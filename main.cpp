#include <cmath>
#include <string>
#include <SFML/Graphics.hpp>
#include "Cannon.h"
#include "Missile.h"
#include "Terrain.h"
#include "EndScreen.h"
#include "InGameUI.h"
#include "Menu.h"
#include "Help.h"

using namespace std;

sf::Vector2f generate_spawn_point_on(Terrain terrain) {
    sf::Vector2f spawn;
    sf::VertexArray vertices = terrain.get_vertices();

    spawn.x = rand() % (int(800-CANNON_SIZE.x) + 1);
    spawn.y = vertices[spawn.x].position.y;
    for (int i=spawn.x; i<=int(spawn.x+CANNON_SIZE.x); i++) {
        if (vertices[i].position.y < spawn.y)
            spawn.y = vertices[i].position.y;
    }

    return spawn;
}

float generate_wind() {
    return 0;//float(rand() % ((2*MAX_WIND_STRENGTH + 1) - MAX_WIND_STRENGTH));
}

bool check_if_round_in_progress(bool missile_flying, vector<Cannon*>* cannons) {
    return (!missile_flying and cannons->size() > 1);
}

void check_cannon_events(sf::Event& event, Cannon* cannon, Terrain* terrain, Missile* missile, float *wind_strength) {
    if (event.key.code == sf::Keyboard::Left)
        cannon->move_on(terrain, side("left"), CANNON_MOVE_AMOUNT);
    else if (event.key.code == sf::Keyboard::Right)
        cannon->move_on(terrain, side("right"), CANNON_MOVE_AMOUNT);
    else if (event.key.code == sf::Keyboard::Up)
        cannon->rotate_barrel(side("up"));
    else if (event.key.code == sf::Keyboard::Down)
        cannon->rotate_barrel(side("down"));
    else if (event.key.code == sf::Keyboard::Space) {
        map<string, sf::Vector2f> parameters = cannon->get_missile_params(wind_strength);
        missile->set_parameters(parameters, sf::Color::Black);
    } else if (event.key.code == sf::Keyboard::A)
        cannon->change_shot_strength(SHOT_STRENGTH_DELTA);
    else if (event.key.code == sf::Keyboard::Z)
        cannon->change_shot_strength(-SHOT_STRENGTH_DELTA);
}

bool cannon_hit(Cannon* cannon, Missile* missile) {
    return (cannon->in_explosion(missile->get_position(), missile->get_explosion_radius()));
}

void handle_cannon_destruction(vector<Cannon *> &cannons, int &i, sf::RenderWindow & window, Terrain *terrain) {
    Cannon* cannon = cannons[i];
    map<string, sf::Vector2f> parameters = cannon->get_destruction_params();

    auto* phantom = new Missile(parameters, sf::Color::Transparent);
    phantom->explode(window);
    terrain->destroy(phantom->get_position(), phantom->get_explosion_radius());

    int j = 0;
    while (j < cannons.size()) {
        if (cannons[j]->in_explosion(phantom->get_position(), phantom->get_explosion_radius()))
            cannons[j]->lower_hp(int(phantom->get_radius()*8));

        j += 1;
    }

    delete phantom;

    cannons.erase(cannons.begin() + i);
}

void handle_cannon_hit(sf::RenderWindow &window, vector<Cannon *> &cannons, int i, Missile *missile) {
    Cannon* cannon = cannons[i];
    cannon->lower_hp(int(missile->get_radius() * 8));
}

void handle_explosion(sf::RenderWindow &window, vector<Cannon *> &cannons, Missile *missile, Terrain *terrain) {
    missile->explode(window);
    terrain->destroy(missile->get_position(), missile->get_radius() * 10);

    int i = 0;
    while (i < cannons.size()) {
        if (cannon_hit(cannons[i], missile))
            handle_cannon_hit(window, cannons, i, missile);
        if (cannons[i]->out_of_screen())
            cannons.erase(cannons.begin() + i);
        i += 1;
    }
}

void new_round(Missile* missile, float* wind_strength, int* turn, vector<Cannon*>* cannons) {
    missile->reset();
    *wind_strength = generate_wind();
    *turn += 1;
    if (*turn >= cannons->size())
        *turn = 0;
}

void run_game(sf::RenderWindow& window, vector<Cannon*>& cannons, int& turn, float& wind_strength, Terrain& terrain, Missile& missile, Help& help) {
    Cannon* cannon;
    if (cannons.size() > 1) {
        cannon = cannons[turn];
        InGameUI UI = InGameUI(cannon, wind_strength);

        window.clear(BACKGROUND_COLOR);
        terrain.draw(window);
        UI.draw(window);
        help.draw(window);

        for (auto i: cannons) {
            if (!i->is_on(terrain) && i->get_hp() > 0)
                i->fall();
            i->draw(window);
        }

        if (missile.flying) {
            missile.draw(window);
            missile.move_over(terrain, cannons);

            if (!missile.flying) {
                handle_explosion(window, cannons, &missile, &terrain);

                new_round(&missile, &wind_strength, &turn, &cannons);
            }
        }

        int i = 0;
        while (i < cannons.size()) {
            if (cannons[i]->get_hp() <= 0)
                handle_cannon_destruction(cannons, i, window, &terrain);
            else
                i += 1;
        }

    } else if (cannons.size() == 1) {
        Cannon* winner = cannons[0];
        EndScreen end(winner->name, winner->get_color());
        end.draw(window);
    } else {
        EndScreen end("Noone! (DRAW)");
        end.draw(window);
    }
}


int main() {
    srand(time(nullptr));

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Artillery", sf::Style::Default, settings);

    Terrain terrain;
    vector<Cannon*> cannons;
    Cannon* cannon;
    Missile missile;

    Menu menu;
    Help help;

    bool round_in_progress = false;
    bool game_started = false;
    int turn = 0;
    float wind_strength = generate_wind();


    string str;
    string name;
    while (window.isOpen())
    {
        if (game_started)
            round_in_progress = check_if_round_in_progress(missile.flying, &cannons);

        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            else if (event.type == sf::Event::KeyPressed && !game_started &&
                     event.key.code == sf::Keyboard::Enter)
                menu.advance_step(game_started, cannons, name, generate_spawn_point_on(terrain));

            else if (event.type == sf::Event::TextEntered && !game_started) {
                if (event.text.unicode > 49 && event.text.unicode < 58 && !menu.chosen_number_of_players) {
                    str = static_cast<char>(event.text.unicode);
                    menu.set_number_of_players(str);
                } else if (event.text.unicode < 128 && menu.chosen_number_of_players) {
                    if(event.text.unicode == 8 && !name.empty()) {
                        name.resize(name.size() - 1);
                        menu.update_name_fields(name);
                    }
                    else {
                        name += static_cast<char>(event.text.unicode);
                        menu.update_name_fields(name);
                    }
                }

            } else if (event.type == sf::Event::KeyPressed && game_started && event.key.code == sf::Keyboard::H) {
                help.switch_display();
            } else if (event.type == sf::Event::KeyPressed && game_started && round_in_progress) {
                cannon = cannons[turn];
                check_cannon_events(event, cannon, &terrain, &missile, &wind_strength);
            }
        }

        if (game_started) {
            run_game(window, cannons, turn, wind_strength, terrain, missile, help);
        } else {
            window.clear(BACKGROUND_COLOR);
            menu.draw(window);
        }

        window.display();
    }

    return 0;
}
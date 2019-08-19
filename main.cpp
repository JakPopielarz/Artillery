#include <cmath>
#include <string>
#include <SFML/Graphics.hpp>
#include "Cannon.h"
#include "Missile.h"
#include "Terrain.h"
#include "EndScreen.h"
#include "InGameUI.h"

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
    return float(rand() % ((2*MAX_WIND_STRENGTH + 1) - MAX_WIND_STRENGTH));
}

bool check_if_game_in_progress(bool missile_flying, vector<Cannon*>* cannons) {
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
        missile->set_parameters(cannon->shoot(wind_strength), sf::Color::Black);
    } else if (event.key.code == sf::Keyboard::A)
        cannon->change_shot_strength(SHOT_STRENGTH_DELTA);
    else if (event.key.code == sf::Keyboard::Z)
        cannon->change_shot_strength(-SHOT_STRENGTH_DELTA);
}

bool cannon_hit(Cannon* cannon, Missile* missile) {
    return (cannon->in_explosion(missile->get_position(), missile->get_radius() * 10));
}

void handle_cannon_hit(vector<Cannon *> &cannons, int i, Missile *missile) {
    Cannon* cannon = cannons[i];
    cannon->lower_hp(int(missile->get_radius() * 8));

    if (cannon->get_hp() <= 0 and cannon->get_position().x >= 0) {
        missile->set_parameters(cannon->destroy(), sf::Color::Transparent);
        cannons.erase(cannons.begin() + i);
    }
}

void handle_destruction(sf::RenderWindow &window, vector<Cannon *> &cannons, Missile *missile, Terrain *terrain) {
    missile->explode(window);
    terrain->destroy(missile->get_position(), missile->get_radius() * 10);

    int i = 0;
    while (i < cannons.size()) {
        if (cannon_hit(cannons[i], missile))
            handle_cannon_hit(cannons, i, missile);
        if (cannons[i]->out_of_screen())
            cannons.erase(cannons.begin() + i);
        i += 1;
    }
}

int main() {
    srand(time(nullptr));

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Artillery", sf::Style::Default, settings);

    Terrain terrain;
    vector<Cannon*> cannons;
    cannons.emplace_back(new Cannon(generate_spawn_point_on(terrain), sf::Color::Magenta, "Magenta"));
    cannons.emplace_back(new Cannon(generate_spawn_point_on(terrain), sf::Color::Green, "Green"));
    cannons.emplace_back(new Cannon(generate_spawn_point_on(terrain), sf::Color::Yellow, "Yellow"));
    //cannons.emplace_back(new Cannon(generate_spawn_point_on(terrain), sf::Color::Black, "Black"));
    Cannon* cannon;
    Missile missile;
    bool game_in_progress;
    int turn = 0;
    float wind_strength = generate_wind();

    while (window.isOpen())
    {
        game_in_progress = check_if_game_in_progress(missile.flying, &cannons);

        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed and game_in_progress) {
                cannon = cannons[turn];
                check_cannon_events(event, cannon, &terrain, &missile, &wind_strength);
            }
        }

        if (cannons.size() > 1) {
            cannon = cannons[turn];
            InGameUI UI = InGameUI(cannon, wind_strength);

            window.clear(sf::Color(139, 194, 239));
            terrain.draw(window);
            UI.draw(window);

            for (auto i: cannons) {
                if (!i->is_on(terrain) && i->get_hp() > 0)
                    i->fall();
                i->draw(window);
            }

            if (missile.flying) {
                missile.draw(window);
                missile.move_over(terrain, cannons);

                if (!missile.flying) {
                    handle_destruction(window, cannons, &missile, &terrain);

                    if (!missile.flying) {
                        missile.reset();
                        wind_strength = generate_wind();

                        turn += 1;
                        if (turn >= cannons.size())
                            turn = 0;
                    }
                }
            }
        } else if (cannons.size() == 1) {
            Cannon* winner = cannons[0];
            EndScreen end(winner->name, winner->get_color());
            end.draw(window);
        } else {
            EndScreen end("Noone! (DRAW)");
            end.draw(window);
        }

        window.display();
    }

    return 0;
}

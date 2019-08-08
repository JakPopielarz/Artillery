#include <iostream>
#include <math.h>
#include <string>
#include <SFML/Graphics.hpp>
#include "Cannon.h"
#include "Terrain.h"
#include "EndScreen.h"
#include "InGameUI.h"

using namespace std;

sf::Vector2f generate_spawn_point_on(Terrain terrain) {
    sf::Vector2f spawn;
    sf::VertexArray vertices = terrain.get_vertices();

    spawn.x = rand() % (int(800-CANNON_SIZE.x) + 1);
    spawn.y = vertices[spawn.x].position.y;
    for (float i=spawn.x; i<=spawn.x+CANNON_SIZE.x; i++) {
        if (vertices[i].position.y < spawn.y)
            spawn.y = vertices[i].position.y;
    }

    return spawn;
}

int main() {
    srand(time(NULL));


    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Artillery", sf::Style::Default, settings);

    Terrain terrain;
    vector<Cannon*> cannons;
    cannons.emplace_back(new Cannon(generate_spawn_point_on(terrain), sf::Color::Magenta, "Kuba"));
    cannons.emplace_back(new Cannon(generate_spawn_point_on(terrain), sf::Color::Green, "Asia"));
    cannons.emplace_back(new Cannon(generate_spawn_point_on(terrain), sf::Color::Yellow, "Yellow"));
    cannons.emplace_back(new Cannon(generate_spawn_point_on(terrain), sf::Color::Black, "Black"));
    Cannon* cannon;
    Missile missile;
    bool shot_in_progress = false;
    int turn = 0;

    while (window.isOpen())
    {
        sf::Event event;
        if (event.type == sf::Event::Closed)
            window.close();

        if (cannons.size() > 1) {
            cannon = cannons[turn];
            InGameUI UI = InGameUI(cannon);
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::KeyPressed and !shot_in_progress and cannon->get_hp() > 0) {
                    if (event.key.code == sf::Keyboard::Left)
                        cannon->move_on(terrain, side("left"), CANNON_MOVE_AMOUNT);
                    else if (event.key.code == sf::Keyboard::Right)
                        cannon->move_on(terrain, side("right"), CANNON_MOVE_AMOUNT);
                    else if (event.key.code == sf::Keyboard::Up)
                        cannon->rotate_barrel(side("up"));
                    else if (event.key.code == sf::Keyboard::Down)
                        cannon->rotate_barrel(side("down"));
                    else if (event.key.code == sf::Keyboard::Space) {
                        missile = cannon->shoot();
                        shot_in_progress = true;
                    } else if (event.key.code == sf::Keyboard::A)
                        cannon->change_shot_strength(SHOT_STRENGTH_DELTA);
                    else if (event.key.code == sf::Keyboard::Z)
                        cannon->change_shot_strength(-SHOT_STRENGTH_DELTA);
                }
            }

            window.clear(sf::Color(139, 194, 239));
            terrain.draw(window);
            UI.draw(window);
            for (auto i: cannons) {
                if (!i->is_on(terrain) && i->get_hp() > 0)
                    i->fall();
                i->draw(window);
            }

            if (shot_in_progress) {
                missile.draw(window);
                missile.move_over(terrain);
                shot_in_progress = missile.flying;
                if (!shot_in_progress) {
                    terrain.destroy(missile.get_position(), missile.get_radius() * 10);

                    int i = 0;
                    while (i < cannons.size()) {
                        if (cannons[i]->in_explosion(missile.get_position(), missile.get_radius() * 10))
                            cannons[i]->lower_hp(int(missile.get_radius() * 8));

                        if (cannons[i]->get_hp() <= 0 and cannons[i]->get_position().x >= 0) {
                            missile = cannons[i]->destroy();
                            shot_in_progress = true;
                        }

                        if (cannons[i]->get_position().x < 0)
                            cannons.erase(cannons.begin() + i);

                        i += 1;
                    }

                    if (!shot_in_progress) {
                        missile.reset();

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

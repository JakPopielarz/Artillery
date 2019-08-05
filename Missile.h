//
// Created by kinga on 5/20/19.
//

#ifndef ARTILLERY_MISSILE_H
#define ARTILLERY_MISSILE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>
#include "Constants.h"
#include "Terrain.h"

using namespace std;

class Missile {
private:
    sf::CircleShape missile;
    sf::Vector2f velocity;

public:
    bool flying = false;

    Missile() { Missile(sf::Vector2f(-1000, - 1000), sf::Vector2f(0,0)); };
    Missile(float starting_x, float starting_y, float starting_velocity, float alpha, float wind_x=0, float wind_y=0, float size=3, sf::Color color=sf::Color::Black);
    Missile(sf::Vector2f starting_position, sf::Vector2f starting_velocity, sf::Vector2f wind=sf::Vector2f(0,0), float size=3, sf::Color color=sf::Color::Black);
    sf::Vector2f get_position() { return missile.getPosition(); };
    sf::Vector2f get_velocity() { return velocity; };
    void set_position(sf::Vector2f new_position) { missile.setPosition(new_position); }
    void set_velocity(sf::Vector2f new_velocity) { velocity=new_velocity; }
    void draw(sf::RenderWindow& window);
    void move_over(Terrain& terrain);
    void reset();
    bool check_flying_over(Terrain& terrain);
};

#endif //ARTILLERY_MISSILE_H

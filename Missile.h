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

class Missile {
private:
    sf::CircleShape missile;
    sf::Vector2f velocity;
    float wind_strength;
public:
    bool flying = false;

    Missile();
    Missile(sf::Vector2f starting_position, sf::Vector2f starting_velocity, float wind=0, float size=2, sf::Color color=sf::Color::Black);
    sf::Vector2f get_position() { return missile.getPosition(); };
    sf::Vector2f get_velocity() { return velocity; };
    float get_radius() { return  missile.getRadius(); };
    void set_position(sf::Vector2f new_position) { missile.setPosition(new_position); }
    void set_velocity(sf::Vector2f new_velocity) { velocity=new_velocity; }
    void draw(sf::RenderWindow& window);
    void move_over(Terrain& terrain);
    void reset();
    bool check_flying_over(Terrain& terrain);
};

#endif //ARTILLERY_MISSILE_H

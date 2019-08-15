//
// Created by kinga on 5/20/19.
//

#ifndef ARTILLERY_MISSILE_H
#define ARTILLERY_MISSILE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include "Constants.h"
#include "Terrain.h"
#include "Cannon.h"

using namespace std;

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
    void set_color(sf::Color color) { missile.setFillColor(color); }
    void set_wind(float wind) { wind_strength = wind; }
    void draw(sf::RenderWindow& window);
    void move_over(Terrain& terrain, vector<Cannon*>& cannons);
    bool check_flying_over(Terrain& terrain);
    bool check_collision_with(vector<Cannon*>& cannons);
    bool in_cannon(Cannon* cannon);
    void reset();
    void explode(sf::RenderWindow& window);
    bool on_screen();
};

#endif //ARTILLERY_MISSILE_H

//
// Created by kinga on 5/20/19.
//

#ifndef ARTILLERY_MISSILE_H
#define ARTILLERY_MISSILE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include "Constants.h"
#include "Terrain.h"
#include "Cannon.h"

using namespace std;

class Missile {
private:
    sf::CircleShape missile;
    sf::Vector2f velocity;
    float wind_strength;
    float explosion_coefficient;
public:
    bool flying = false;

    Missile();
    Missile(map<string, sf::Vector2f> parameters, sf::Color color) { set_parameters(parameters, color); }
    sf::Vector2f get_position() { return missile.getPosition(); };
    sf::Vector2f get_velocity() { return velocity; };
    float get_radius() { return  missile.getRadius(); };
    float get_explosion_radius() { return explosion_coefficient*get_radius(); }
    void set_position(sf::Vector2f new_position) { missile.setPosition(new_position); }
    void set_velocity(sf::Vector2f new_velocity) { velocity=new_velocity; }
    void set_color(sf::Color color) { missile.setFillColor(color); }
    void set_wind(float wind) { wind_strength = wind; }
    void set_parameters(map<string, sf::Vector2f>& parameters, sf::Color color);
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

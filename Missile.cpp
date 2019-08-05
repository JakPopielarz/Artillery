//
// Created by kinga on 5/20/19.
//

#include "Missile.h"
using namespace std;

Missile::Missile(float starting_x, float starting_y, float starting_velocity, float alpha, float wind_x, float wind_y, float size, sf::Color color) {
    velocity = sf::Vector2f(cos(alpha)*starting_velocity+wind_x, sin(alpha)*starting_velocity+wind_y);
    missile.setRadius(size);
    missile.setPosition(starting_x, starting_y);
    missile.setFillColor(color);
}

Missile::Missile(sf::Vector2f starting_position, sf::Vector2f starting_velocity, sf::Vector2f wind, float size, sf::Color color) {
    velocity = starting_velocity + wind;
    missile.setRadius(size);
    missile.setPosition(starting_position);
    missile.setFillColor(color);
}

void Missile::draw(sf::RenderWindow &window) {
    window.draw(missile);
}
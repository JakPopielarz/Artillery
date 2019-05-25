//
// Created by jakub on 12.05.19.
//

#include "Cannon.h"

Cannon::Cannon(float position_x, float position_y, sf::Color colour) {
    Point position = Point(position_x, position_y);
    position_ = position;

    colour_ = colour;
    health_points_ = 100;
    cannon_angle_ = 90;
    width = 20;
    height = 10;

}

void Cannon::draw(sf::RenderWindow& window) {
    sf::RectangleShape cannon;
    cannon.setSize(sf::Vector2f(width, height));
    cannon.setFillColor(colour_);
    cannon.setOutlineThickness(-1.f);
    cannon.setOutlineColor(sf::Color::Black);
    cannon.setPosition(position_.get_x(), position_.get_y()-height);
    window.draw(cannon);

    sf::RectangleShape barrel(sf::Vector2f(12, 1));
    barrel.setFillColor(sf::Color::Black);
    barrel.setPosition(position_.get_x()+width/2, position_.get_y()-height/2);
    barrel.rotate(-cannon_angle_);
    window.draw(barrel);

}

Missile Cannon::shoot(float force, float wind[]) {
    return Missile(position_.get_x()+width/2, position_.get_y()-height/2, force, cannon_angle_, wind[0], wind[1]);
}


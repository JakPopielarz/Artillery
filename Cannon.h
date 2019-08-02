//
// Created by jakub on 12.05.19.
//

#ifndef ARTILLERY_CANNON_H
#define ARTILLERY_CANNON_H

#include <SFML/Graphics.hpp>
#include "Point.h"
#include "Missile.h"

class Cannon {
private:
    int health_points_;
    Point position_; //of the lower-left corner
    float cannon_angle_;
    sf::RectangleShape cannon;
    sf::RectangleShape barrel;
    float width;
    float height;
public:
    explicit Cannon(float position_x, float position_y, sf::Color colour);
    int get_hp() { return health_points_; }
    Point& get_position() { return position_; }
    void set_hp(int hp) { health_points_ = hp; }
    void lower_hp(int amount) { health_points_ -= amount; }
    void set_position(Point position) { position_ = position; }
    void set_angle(float angle) { cannon_angle_ = angle; }
    float get_angle() { return cannon_angle_; }
    void change_angle(float amount) { cannon_angle_ += amount; }
    Missile shoot(float, float*);
    void draw(sf::RenderWindow& window);
};


#endif //ARTILLERY_CANNON_H

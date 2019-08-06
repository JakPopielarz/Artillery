//
// Created by jakub on 12.05.19.
//

#ifndef ARTILLERY_CANNON_H
#define ARTILLERY_CANNON_H

#include <SFML/Graphics.hpp>
#include "Point.h"
#include "Missile.h"
#include "Terrain.h"

typedef struct side {
    string direction;
    sf::Vector2f vector;

    explicit side(const string& side_) {
        direction = side_;
        if (side_ == "up")
            vector = sf::Vector2f(0, -1);
        else if (side_ == "down")
            vector = sf::Vector2f(0, 1);
        else if (side_ == "left")
            vector = sf::Vector2f(-1, 0);
        else if (side_ == "right")
            vector = sf::Vector2f(1, 0);
    }

    sf::Vector2f get_vector() {
        return vector;
    }
} side;


class Cannon {
private:
    sf::Font font;
    int hit_points_int;
    sf::Text hit_points;
    sf::RectangleShape cannon;
    sf::RectangleShape barrel;
    float width;
    float height;
    float fall_velocity;
public:
    explicit Cannon(float position_x, float position_y, sf::Color colour);
    int get_hp() { return hit_points_int; }
    sf::Vector2f get_position() { return cannon.getPosition(); }
    void set_hp(int hp) { hit_points_int = hp; }
    void lower_hp(int amount);
    void set_position(sf::Vector2f position) { cannon.setPosition(position); }
    void set_position(float position_x, float position_y) { cannon.setPosition(position_x, position_y); }
    void set_angle(float angle) { barrel.setRotation(angle); }
    float get_angle() { return barrel.getRotation(); }
    void change_angle(float amount) { barrel.rotate(amount); }
    Missile shoot();
    void draw(sf::RenderWindow& window);
    void display_hit_points(sf::RenderWindow& window);
    bool is_on(Terrain);
    void move_on(Terrain terrain, side side, float amount);
    void fall();
    void rotate_barrel(side side);
    bool in_explosion(sf::Vector2f location, float radius);
    Missile destroy();
};


#endif //ARTILLERY_CANNON_H

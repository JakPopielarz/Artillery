//
// Created by jakub on 12.05.19.
//

#ifndef ARTILLERY_CANNON_H
#define ARTILLERY_CANNON_H

#include <iostream>
#include <map>
#include <SFML/Graphics.hpp>
#include "Terrain.h"

using namespace std;

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
    int hit_points_int;
    sf::RectangleShape cannon;
    sf::RectangleShape barrel;
    float fall_velocity;
    float shot_strength;
public:
    string name;
    explicit Cannon(sf::Vector2f position, sf::Color colour, string nick);
    int get_hp() { return hit_points_int; }
    sf::Vector2f get_position() { return cannon.getPosition(); }
    void set_hp(int hp) { hit_points_int = hp; }
    void lower_hp(int amount);
    void set_position(sf::Vector2f position) { cannon.setPosition(position); }
    void set_position(float position_x, float position_y) { cannon.setPosition(position_x, position_y); }
    void set_angle(float angle) { barrel.setRotation(angle); }
    float get_angle() { return barrel.getRotation(); }
    void change_angle(float amount) { barrel.rotate(amount); }
    float get_shot_strength() { return shot_strength; }
    void change_shot_strength(float amount);
    sf::Color get_color() { return cannon.getFillColor(); }
    map<string, sf::Vector2f> get_missile_params(const float *wind_strength);
    void draw(sf::RenderWindow& window);
    bool is_on(Terrain);
    void move_on(Terrain *terrain, side side, float amount);
    void fall();
    void rotate_barrel(const side& side);
    bool in_explosion(sf::Vector2f location, float radius);
    bool out_of_screen();
    map<string, sf::Vector2f> get_destruction_params();
};

#endif //ARTILLERY_CANNON_H

//
// Created by kinga on 5/20/19.
//

#include "Missile.h"

Missile::Missile(float starting_x, float starting_y, float velocity_x, float velocity_y) {
    this->starting_x = starting_x;
    this->starting_y = starting_y;
    this->velocity_x = velocity_x;
    this->velocity_y = velocity_y;
}

std::vector<float> Missile::get_current_position() {
    std::vector<float> position;
    position.push_back(this->starting_x);
    position.push_back(this->starting_y);
    return position;
}

std::vector<float> Missile::get_current_velocity() {
    std::vector<float> velocity;
    velocity.push_back(this->velocity_x);
    velocity.push_back(this->velocity_y);
    return velocity;
}

void Missile::set_velocity(float vx, float vy) {
    this->velocity_x=vx;
    this->velocity_y=vy;

}

void Missile::set_position(float px, float py) {
    this->starting_x=px;
    this->starting_y=py;

}

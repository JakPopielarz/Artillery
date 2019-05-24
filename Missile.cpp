//
// Created by kinga on 5/20/19.
//

#include "Missile.h"
using namespace std;

Missile::Missile(float starting_x, float starting_y, float velocity, float alpha, float wind_x, float wind_y) {
    this->current_x = starting_x;
    this->current_y = starting_y;
    this->velocity_x = cos(alpha) * velocity + wind_x;
    this->velocity_y = sin(alpha) * velocity + wind_y;
}

vector<float> Missile::get_current_position() {
    vector<float> position;
    position.push_back(this->current_x);
    position.push_back(this->current_y);
    return position;
}

vector<float> Missile::get_current_velocity() {
    vector<float> velocity;
    velocity.push_back(this->velocity_x);
    velocity.push_back(this->velocity_y);
    return velocity;
}

void Missile::set_velocity(float velocity_x, float velocity_y) {
    this->velocity_x=velocity_x;
    this->velocity_y=velocity_y;
}

void Missile::set_position(float position_x, float position_y) {
    this->current_x=position_x;
    this->current_y=position_y;
}

sf::CircleShape Missile::shape() {
    //the function returns a circle shape with the properties for a specific missile
    //so if you want to draw a missile in main window you need to call a function like that:
    //window.draw(missile_object.shape())
    sf::CircleShape missile;
    missile.setRadius(this->radius);
    missile.setPosition(this->current_x, this->current_y);
    missile.setFillColor(sf::Color(255, 0, 0)); //we can change it due to the type of missile (defined by the radius)
    // ^ also can add texture or outline etc.
    return missile;

}

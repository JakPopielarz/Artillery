//
// Created by kinga on 5/20/19.
//

#ifndef JIMPPROJEKT_MISSILE_H
#define JIMPPROJEKT_MISSILE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>
using namespace std;

class Missile {
private:
    float current_x, current_y;
    float velocity_x, velocity_y;
    float radius; //also can be used as a power of destruction ;)

public:
    Missile(float starting_x, float starting_y, float velocity, float alpha, float wind_x, float wind_y);
    vector<float> get_current_position();
    vector<float> get_current_velocity();
    void set_position(float position_x, float position_y);
    void set_velocity(float velocity_x, float velocity_y);
    sf::CircleShape shape(); //read the implementation first ;)
    ~Missile()= default;

};


#endif //JIMPPROJEKT_MISSILE_H

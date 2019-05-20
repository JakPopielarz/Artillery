//
// Created by jakub on 12.05.19.
//

#ifndef ARTILLERY_CANNON_H
#define ARTILLERY_CANNON_H

#include "Point.h"

class Cannon {
private:
    int health_points_;
    Point &position_;
public:
    explicit Cannon(Point &position): health_points_{100}, position_{position}{}
    int get_hp() { return health_points_; }
    Point& get_position() { return position_; }
    void set_hp(int hp) { health_points_ = hp; }
    void lower_hp(int amount) { health_points_ -= amount; }
    void set_position(Point position) { position_ = position; }
};


#endif //ARTILLERY_CANNON_H

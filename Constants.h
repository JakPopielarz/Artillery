#ifndef ARTILLERY_CONSTANTS_H
#define ARTILLERY_CONSTANTS_H

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;
const float MAX_FALL_VELOCITY = 0.9f;
const float GRAVITY_SPEED = 0.03f;
const sf::Vector2f CANNON_SIZE(16,10);
const float CANNON_MOVE_AMOUNT = 0.5f;
const float MAX_MOVEMENT_ELEVATION = 3;
const float BARREL_ROTATION_AMOUNT = 2.5f;
const float BARREL_MIN_ROTATION = 180;
const float BARREL_MAX_ROTATION = 360;
const float CANNON_EXPLOSION_SIZE = 5;

#endif //ARTILLERY_CONSTANTS_H

#ifndef ARTILLERY_CONSTANTS_H
#define ARTILLERY_CONSTANTS_H

#include "SFML/Graphics.hpp"

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;
const float WINDOW_MARGIN = 10;
const sf::Color BACKGROUND_COLOR = sf::Color(139, 194, 239);

const float  MAX_FALL_VELOCITY = 0.9f;
const float GRAVITY_SPEED = 0.03f;

const sf::Vector2f CANNON_SIZE(16,10);
const float CANNON_MOVE_AMOUNT = 0.5f;
const float CANNON_EXPLOSION_RADIUS = 5;
const float MAX_MOVEMENT_ELEVATION = 3;

const float BARREL_ROTATION_AMOUNT = 2.5f;
const float BARREL_MIN_ROTATION = 180;
const float BARREL_MAX_ROTATION = 360;

const float SHOT_STRENGTH_DELTA = 2.5f;
const float MAX_SHOT_STRENGTH = 15;
const float MISSILE_EXPLOSION_INCREMENT = 0.15;

const float WIND_ARROW_WIDTH = 3;
const sf::Vector2f WIND_TEXT_POSITION = sf::Vector2f(WINDOW_WIDTH/2.f, WINDOW_MARGIN);
const unsigned int WIND_CHAR_SIZE = 10;
const int MAX_WIND_STRENGTH = 10;
const float WIND_IMPACT_ON_FLIGHT = 0.0015;

#endif //ARTILLERY_CONSTANTS_H

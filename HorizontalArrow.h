
//
// Created by jakub on 8/10/19.
//

#ifndef ARTILLERY_HORIZONTALARROW_H
#define ARTILLERY_HORIZONTALARROW_H

#include <cmath>
#include "SFML/Graphics.hpp"
#include "Constants.h"

class HorizontalArrow {
private:
    sf::RectangleShape stem;
    sf::CircleShape tip;
public:
    HorizontalArrow(float length, sf::Vector2f position);
    void draw(sf::RenderWindow& window);
    void set_position(sf::Vector2f position);
    void set_length(float length);
};


#endif //ARTILLERY_HORIZONTALARROW_H

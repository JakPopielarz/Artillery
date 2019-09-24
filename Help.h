//
// Created by jakub on 9/24/19.
//

#ifndef ARTILLERY_HELP_H
#define ARTILLERY_HELP_H


#include <SFML/Graphics.hpp>
#include <iostream>
#include "Constants.h"

class Help {
private:
    bool display_help;
    sf::Font font;
    sf::Text controls;
public:
    Help();
    void draw(sf::RenderWindow &window);
    void switch_display();
};


#endif //ARTILLERY_HELP_H

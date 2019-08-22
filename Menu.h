//
// Created by jakub on 8/22/19.
//

#ifndef ARTILLERY_MENU_H
#define ARTILLERY_MENU_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Constants.h"

class Menu {
private:
    sf::Font font;
    sf::Text controls;
public:
    Menu();
    void draw(sf::RenderWindow& window);
};


#endif //ARTILLERY_MENU_H

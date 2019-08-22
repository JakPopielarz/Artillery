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
    sf::Text number_of_players_field;
    int number_of_players;
public:
    Menu();
    void draw(sf::RenderWindow& window);
    void set_number_of_players(std::string& number);
};


#endif //ARTILLERY_MENU_H

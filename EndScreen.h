//
// Created by jakub on 07.08.19.
//

#ifndef ARTILLERY_END_SCREEN_H
#define ARTILLERY_END_SCREEN_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Constants.h"

using namespace std;

class EndScreen {
private:
    sf::Font font;
    sf::Text header;
    sf::Text follow_up;
public:
    explicit EndScreen(const string& winner, sf::Color color=sf::Color::Black);
    void draw(sf::RenderWindow& window);
};


#endif //ARTILLERY_END_SCREEN_H

//
// Created by jakub on 9/24/19.
//

#include "Help.h"

using namespace std;

Help::Help() {
    display_help = false;

    if (!font.loadFromFile("../Resources/Fonts/ALoveofThunder.ttf")) {
        cout << "Error loading font from file" << endl;
        system("pause");
    }

    controls.setFont(font);
    controls.setFillColor(sf::Color::Black);
    controls.setCharacterSize(HELP_CHARACTER_SIZE);
    controls.setString(CONTROLS_STRING);
    controls.setOrigin(controls.getGlobalBounds().left+controls.getGlobalBounds().width/2,
                       controls.getGlobalBounds().top+controls.getGlobalBounds().height/2);
    controls.setPosition(sf::Vector2f(WINDOW_WIDTH/2.f, WINDOW_HEIGHT/2.f));
}

void Help::draw(sf::RenderWindow &window) {
    if (display_help)
        window.draw(controls);
}

void Help::switch_display() {
    display_help = !display_help;
}

//
// Created by jakub on 8/22/19.
//

#include "Menu.h"

using namespace std;

Menu::Menu() {
    if (!font.loadFromFile("../Resources/Fonts/ALoveofThunder.ttf")) {
        cout << "Error loading font from file" << endl;
        system("pause");
    }

    controls.setFont(font);
    controls.setFillColor(sf::Color::White);
    controls.setString(
            "CONTROLS:\n"
            "left and right arrow: move\n"
            "up and down arrow: rotate barrel\n"
            "a and z: adjust shot strength\n"
            "space: shoot"
            );
    controls.setCharacterSize(18);
    controls.setPosition(sf::Vector2f(WINDOW_MARGIN, WINDOW_MARGIN));
}

void Menu::draw(sf::RenderWindow &window) {
    window.draw(controls);
}

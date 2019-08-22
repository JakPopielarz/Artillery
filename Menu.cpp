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
            "CONTROLS\n\n"
            "left and right arrow\n"
            "move\n\n"
            "up and down arrow\n"
            "rotate barrel\n\n"
            "a and z\n"
            "adjust shot strength\n\n"
            "space\n"
            "shoot\n\n"
            "enter\n"
            "start the game"
            );
    controls.setCharacterSize(MENU_CHARACTER_SIZE);
    controls.setPosition(sf::Vector2f(WINDOW_MARGIN, WINDOW_MARGIN));

    number_of_players = 2;
    number_of_players_field.setFont(font);
    number_of_players_field.setFillColor(sf::Color::White);
    number_of_players_field.setString("Number of players (2-9): 2");
    number_of_players_field.setCharacterSize(MENU_CHARACTER_SIZE + 2);
    number_of_players_field.setPosition(sf::Vector2f(WINDOW_MARGIN, WINDOW_HEIGHT - WINDOW_MARGIN - MENU_CHARACTER_SIZE - 2));
}

void Menu::set_number_of_players(std::string& number) {
    number_of_players_field.setString("Number of players (2-9): " + number);
    number_of_players = stoi(number);
}

void Menu::draw(sf::RenderWindow &window) {
    window.draw(controls);
    window.draw(number_of_players_field);
}

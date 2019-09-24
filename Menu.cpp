//
// Created by jakub on 8/22/19.
//

#include "Menu.h"

using namespace std;

Menu::Menu() {
    chosen_number_of_players = false;
    players_generated_count = 0;

    if (!font.loadFromFile("../Resources/Fonts/ALoveofThunder.ttf")) {
        cout << "Error loading font from file" << endl;
        system("pause");
    }

    controls.setFont(font);
    controls.setFillColor(sf::Color::White);
    controls.setString(CONTROLS_STRING +
            "enter\n"
            "confirm number of players"
            );
    controls.setCharacterSize(MENU_CHARACTER_SIZE);
    controls.setPosition(sf::Vector2f(WINDOW_MARGIN, WINDOW_MARGIN));

    number_of_players = 2;
    number_of_players_field.setFont(font);
    number_of_players_field.setFillColor(sf::Color::Black);
    number_of_players_field.setString("Number of players (2-9): 2");
    number_of_players_field.setCharacterSize(MENU_CHARACTER_SIZE + 2);
    number_of_players_field.setPosition(WINDOW_MARGIN, WINDOW_HEIGHT-WINDOW_MARGIN-MENU_CHARACTER_SIZE-2);
}

void Menu::draw(sf::RenderWindow& window) {
    window.draw(controls);
    window.draw(number_of_players_field);
    display_name_fields(window);
}

void Menu::display_name_fields(sf::RenderWindow& window) {
    for (auto& field : name_fields)
        window.draw(field);
}

void Menu::set_number_of_players(std::string& number) {
    if (!chosen_number_of_players) {
        number_of_players_field.setString("Number of players (2-9): " + number);
        number_of_players = stoi(number);
    }
}

void Menu::set_enter_function_text(std::string function_text) {
    controls.setString(CONTROLS_STRING + "enter\n" + function_text);
}

void Menu::advance_step(bool& game_started, vector<Cannon*>& cannons, string& player_name, sf::Vector2f spawn_point) {
    if(!chosen_number_of_players) {
        chosen_number_of_players = true;
        set_enter_function_text("confirm player " + to_string(players_generated_count+1) + " name");
        create_name_fields();
    } else if (players_generated_count < number_of_players-2) {
        generate_player(cannons, spawn_point, player_name);
        set_enter_function_text("confirm player " + to_string(players_generated_count+1) + " name");
        player_name = "";
    } else if (players_generated_count == number_of_players-2) {
        generate_player(cannons, spawn_point, player_name);
        set_enter_function_text("confirm player " + to_string(players_generated_count+1) + " name\nand start game");
        player_name = "";
    } else {
        generate_player(cannons, spawn_point, player_name);
        set_enter_function_text("game started");
        game_started = true;
    }
}

void Menu::create_name_fields() {
    for (int i=1; i<=number_of_players; i++) {
        name_fields.emplace_back(sf::Text(to_string(i)+": ", font, MENU_CHARACTER_SIZE+2));
        name_fields[i-1].setPosition(WINDOW_WIDTH/2.f+WINDOW_MARGIN, float(i-1)*(WINDOW_MARGIN+MENU_CHARACTER_SIZE));
        name_fields[i-1].setFillColor(player_colors[i-1]);
    }
}

void Menu::update_name_fields(string& name) {
    name_fields[players_generated_count].setString(to_string(players_generated_count+1)+": " + name);
}

void Menu::generate_player(vector<Cannon *>& cannons, sf::Vector2f spawn_point, std::string& player_name) {
    cannons.emplace_back(new Cannon(spawn_point, player_colors[players_generated_count], player_name));
    players_generated_count += 1;
}

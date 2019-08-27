//
// Created by jakub on 8/22/19.
//

#ifndef ARTILLERY_MENU_H
#define ARTILLERY_MENU_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Cannon.h"
#include "Constants.h"

class Menu {
private:
    std::string controls_string;
    sf::Font font;
    sf::Text controls;
    sf::Text number_of_players_field;
    int number_of_players;
    int players_generated_count;
    vector<sf::Text> name_fields;
    sf::Color player_colors[9] = {sf::Color::Magenta, sf::Color::Green,
                                  sf::Color::Blue, sf::Color::Yellow,
                                  sf::Color::Black, sf::Color::White,
                                  sf::Color::Red, sf::Color::Cyan,
                                  sf::Color(255, 102, 0)};
public:
    bool chosen_number_of_players;

    Menu();
    void draw(sf::RenderWindow& window);
    void display_name_fields(sf::RenderWindow& window);
    int get_players_generated() { return players_generated_count == number_of_players; }
    void set_number_of_players(std::string& number);
    void set_enter_function_text(std::string function_text);
    void advance_step(bool& game_started, vector<Cannon*>& cannons, std::string& player_name, sf::Vector2f spawn_point);
    void create_name_fields();
    void update_name_fields(std::string& name);
    void generate_player(vector<Cannon*>& cannons, sf::Vector2f spawn_point, std::string& player_name);
};


#endif //ARTILLERY_MENU_H

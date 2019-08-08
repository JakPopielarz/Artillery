//
// Created by jakub on 08.08.19.
//

#include "InGameUI.h"

InGameUI::InGameUI(Cannon* cannon) {
    this->cannon = cannon;

    if (!font.loadFromFile("../Resources/Fonts/ALoveofThunder.ttf")) {
        cout << "Error loading font from file" << endl;
        system("pause");
    }
    hit_points.setFont(font);
    string hp_string = "HP: " + to_string(cannon->get_hp());
    hit_points.setString(hp_string);
    hit_points.setPosition(WINDOW_MARGIN, WINDOW_MARGIN);
    hit_points.setFillColor(cannon->get_color());
}

void InGameUI::draw(sf::RenderWindow &window) {
    draw_hit_points(window);
    draw_shot_strength(window);
}

void InGameUI::draw_hit_points(sf::RenderWindow &window) {
    string hp_string = "HP: " + to_string(cannon->get_hp());
    hit_points.setString(hp_string);
    window.draw(hit_points);
}

void InGameUI::draw_shot_strength(sf::RenderWindow &window) {
    string strength_string = "STR: " + to_string(int(cannon->get_shot_strength())) + "%";
    sf::Text strength(strength_string, font);
    strength.setPosition(WINDOW_WIDTH-strength.getGlobalBounds().width-WINDOW_MARGIN, WINDOW_MARGIN);
    strength.setFillColor(cannon->get_color());
    window.draw(strength);
}

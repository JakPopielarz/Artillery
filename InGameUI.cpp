//
// Created by jakub on 08.08.19.
//

#include "InGameUI.h"

InGameUI::InGameUI(Cannon* cannon, float wind_strength) {
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

    wind_text.setFont(font);
    wind_text.setString("wind: ("+to_string(int(wind_strength))+")");
    wind_text.setFillColor(sf::Color::Black);
    wind_text.setCharacterSize(WIND_CHAR_SIZE);
    wind_text.setOrigin(wind_text.getGlobalBounds().left + wind_text.getGlobalBounds().width / 2,
                        wind_text.getGlobalBounds().top);
    wind_text.setPosition(WIND_TEXT_POSITION);

    wind.set_length(wind_strength*10);
    wind.set_position(sf::Vector2f(WINDOW_WIDTH/2.f, WINDOW_MARGIN+20));

    nick.setFont(font);
    nick.setString(cannon->name);
    nick.setPosition(WINDOW_MARGIN, WINDOW_MARGIN+hit_points.getCharacterSize()+WINDOW_MARGIN);
    nick.setFillColor(cannon->get_color());
}

void InGameUI::draw(sf::RenderWindow &window) {
    draw_hit_points(window);
    draw_shot_strength(window);
    draw_wind(window);
}

void InGameUI::draw_hit_points(sf::RenderWindow &window) {
    string hp_string = "HP: " + to_string(cannon->get_hp());
    hit_points.setString(hp_string);
    window.draw(hit_points);
    window.draw(nick);
}

void InGameUI::draw_shot_strength(sf::RenderWindow &window) {
    string strength_string = "STR: " + to_string(int(cannon->get_shot_strength())) + "%";
    sf::Text strength(strength_string, font);
    strength.setPosition(WINDOW_WIDTH-strength.getGlobalBounds().width-WINDOW_MARGIN, WINDOW_MARGIN);
    strength.setFillColor(cannon->get_color());
    window.draw(strength);
}

void InGameUI::draw_wind(sf::RenderWindow& window) {
    window.draw(wind_text);
    wind.draw(window);
}

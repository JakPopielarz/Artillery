//
// Created by jakub on 8/10/19.
//

#include "HorizontalArrow.h"

HorizontalArrow::HorizontalArrow(float length, sf::Vector2f position) {
    stem.setPosition(position);
    stem.setSize(sf::Vector2f(length, WIND_ARROW_WIDTH));
    stem.setFillColor(sf::Color::Black);

    tip = sf::CircleShape(WIND_ARROW_WIDTH*3, 3);
    tip.setOrigin(tip.getOrigin().x+tip.getRadius(), tip.getOrigin().y+tip.getRadius());
    tip.rotate(90*(length/abs(length)));
    tip.setPosition(stem.getPosition().x+length, stem.getPosition().y+WIND_ARROW_WIDTH/2);
    tip.setFillColor(sf::Color::Black);
}

void HorizontalArrow::draw(sf::RenderWindow &window) {
    if (stem.getSize().x > 0) {
        window.draw(stem);
        window.draw(tip);
    }
}

void HorizontalArrow::set_position(sf::Vector2f position) {
    stem.setPosition(position);
    tip.setPosition(stem.getPosition().x+stem.getSize().x, stem.getPosition().y+WIND_ARROW_WIDTH/2);
}

void HorizontalArrow::set_length(float length) {
    stem.setSize(sf::Vector2f(length, WIND_ARROW_WIDTH));
}

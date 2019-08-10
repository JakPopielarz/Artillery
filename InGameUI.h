//
// Created by jakub on 08.08.19.
//

#ifndef ARTILLERY_INGAMEUI_H
#define ARTILLERY_INGAMEUI_H

#include "Constants.h"
#include "Cannon.h"
#include "HorizontalArrow.h"

class InGameUI {
private:
    Cannon* cannon;
    sf::Font font;
    sf::Text hit_points;
    sf::Text wind_text;
    HorizontalArrow wind = HorizontalArrow(30, sf::Vector2f(-1000, -1000));
public:
    explicit InGameUI(Cannon* cannon, float wind_strength);
    void draw(sf::RenderWindow& window);
    void draw_hit_points(sf::RenderWindow &window);
    void draw_shot_strength(sf::RenderWindow& window);
    void draw_wind(sf::RenderWindow& window);
};


#endif //ARTILLERY_INGAMEUI_H

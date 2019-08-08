//
// Created by jakub on 08.08.19.
//

#ifndef ARTILLERY_INGAMEUI_H
#define ARTILLERY_INGAMEUI_H

#include "Constants.h"
#include "Cannon.h"

class InGameUI {
private:
    Cannon* cannon;
    sf::Font font;
    sf::Text hit_points;
public:
    explicit InGameUI(Cannon* cannon);
    void draw(sf::RenderWindow& window);
    void draw_hit_points(sf::RenderWindow &window);
    void draw_shot_strength(sf::RenderWindow& window);
};


#endif //ARTILLERY_INGAMEUI_H

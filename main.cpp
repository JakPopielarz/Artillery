#include <iostream>
#include <SFML/Graphics.hpp>
#include "Point.h"
#include "Cannon.h"
#include "Variables.h"

using namespace std;

int main() {
    float terrain_points[] = {0.f, 100.f, 200.f, 300.f, 400.f};

    Cannon cannon(0, 100, sf::Color::Magenta);

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Artillery");
    sf::ConvexShape terrain(6);
    terrain.setFillColor(sf::Color(35, 147, 67));
    terrain.setOutlineColor(sf::Color::Black);
    terrain.setOutlineThickness(-1);

    for (size_t i=0; i<=TERRAIN_POINT_COUNT; i++) {
        terrain.setPoint(i, sf::Vector2f(i*TERRAIN_POINT_COEFF, WINDOW_HEIGHT-terrain_points[i]));
    }

    terrain.setPoint(TERRAIN_POINT_COUNT+1, sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    terrain.setPoint(TERRAIN_POINT_COUNT+2, sf::Vector2f(0, WINDOW_HEIGHT));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(139, 194, 239));
        window.draw(terrain);
        cannon.draw(window);
        window.display();
    }

    return 0;
}
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Point.h"
#include "Cannon.h"
#include "Terrain.h"

using namespace std;

int main() {
    float terrain_points[] = {0.f, 150.f, 200.f, 433.f};

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Artillery");

    Terrain terrain = Terrain(TERRAIN_POINT_COUNT, terrain_points);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(139, 194, 239));
        terrain.draw(window);
        window.display();
    }

    return 0;
}
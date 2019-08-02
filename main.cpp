#include <iostream>
#include <math.h>
#include <string>
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Point.h"
#include "Cannon.h"
#include "Terrain.h"

using namespace std;

int main() {
    srand(time(NULL));


    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Artillery", sf::Style::Default, settings);

    Terrain terrain;

    Cannon cannon(0, 100, sf::Color::Magenta);

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
        cannon.draw(window);
        window.display();
    }

    return 0;
}
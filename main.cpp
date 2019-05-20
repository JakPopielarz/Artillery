#include <iostream>
#include <SFML/Graphics.hpp>
#include "Point.h"
#include "Cannon.h"

using namespace std;

int main() {
    Point point = Point(2, 14314.4f);
    cout << point << endl;
    Point point2 = Point(-2, -14314);
    point += point2;
    cout << point << endl;
    Cannon cannon = Cannon(point);
    cout << cannon.get_hp() << ", " << cannon.get_position() << endl;

    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
    return 0;
}
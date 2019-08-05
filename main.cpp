#include <iostream>
#include <math.h>
#include <string>
#include <SFML/Graphics.hpp>
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
    Cannon cannon(100, 100, sf::Color::Magenta);
    Missile missile;
    bool shot_in_progress = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed and !shot_in_progress) {
                if (event.key.code == sf::Keyboard::Left)
                    cannon.move_on(terrain, side("left"), CANNON_MOVE_AMOUNT);
                else if (event.key.code == sf::Keyboard::Right)
                    cannon.move_on(terrain, side("right"), CANNON_MOVE_AMOUNT);
                else if (event.key.code == sf::Keyboard::Up)
                    cannon.rotate_barrel(side("up"));
                else if (event.key.code == sf::Keyboard::Down)
                    cannon.rotate_barrel(side("down"));
                else if (event.key.code == sf::Keyboard::Space) {
                    missile = cannon.shoot();
                    shot_in_progress = true;
                }
            }
        }
        if (!cannon.is_on(terrain))
            cannon.fall();

        window.clear(sf::Color(139, 194, 239));
        terrain.draw(window);
        cannon.draw(window);

        if (shot_in_progress) {
            missile.draw(window);
            missile.move_over(terrain);
            shot_in_progress = missile.flying;
        }
        window.display();
    }

    return 0;
}
/*
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Point.h"
#include "Cannon.h"

using namespace std;
bool missile_in_the_air(float missile_x, float missile_y, float terrain[]){ //terrrain to tablica terenu, zmieni� nazwy zmiennych jak b�dzie wrzucony missile
	if(missile_y>terrain[missile_x])
		return true;
	return false;
}
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
    //trzeba pobra� z obiektu px, py, vx i vy
	float gravity = 9.81; // 9,81m/s^2
	float delta_time = 0.01; // 0,01s
	float mis_position[400]; //tablica zapisuj�ca tor ruchu pocisku
	int current_x = px; //obecny indeks w tablicy toru ruchu
	mis_position[current_x] = py; //zapisujemy pozycj� startow� w tablicy po�o�enia
	current_x ++;
	while(missile_in_the_air){ // czy pocisk jest nad ziemi�
		px += vx*delta_time; // zmieniam pozycj� x
		py += (vy*delta_time) - (gravity*delta_time*delta_time/2); //zmieniam pozycj� y
		vy -= gravity+delta_time; //zmieniam pr�dko�� y
		if(px>current_x){ //kiedy po�o�enie pocisku przekroczy indeks x terenu, wtedy
			terrain[current_x] = py;
			current_x++;
		}
		}
    return 0;
}
*/

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Point.h"
#include "Cannon.h"

using namespace std;
bool missile_in_the_air(float missile_x, float missile_y, float terrain[]){ //terrrain to tablica terenu, zmieniê nazwy zmiennych jak bêdzie wrzucony missile
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
    //trzeba pobraæ z obiektu px, py, vx i vy
	float gravity = 9.81; // 9,81m/s^2
	float delta_time = 0.01; // 0,01s
	float mis_position[400]; //tablica zapisuj¹ca tor ruchu pocisku
	int current_x = px; //obecny indeks w tablicy toru ruchu
	mis_position[current_x] = py; //zapisujemy pozycjê startow¹ w tablicy po³o¿enia
	current_x ++;
	while(missile_in_the_air){ // czy pocisk jest nad ziemi¹
		px += vx*delta_time; // zmieniam pozycjê x
		py += (vy*delta_time) - (gravity*delta_time*delta_time/2); //zmieniam pozycjê y
		vy -= gravity+delta_time; //zmieniam prêdkoœæ y
		if(px>current_x){ //kiedy po³o¿enie pocisku przekroczy indeks x terenu, wtedy
			terrain[current_x] = py;
			current_x++;
		}
		}
    return 0;
}

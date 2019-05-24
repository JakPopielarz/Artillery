#include<iostream>
#include<array>
#include<vector>
#include<math.h>
using namespace std;
bool missile_in_the_air(float missile_x, float missile_y, float terrain[]){ //terrrain to tablica terenu, zmieniê nazwy zmiennych jak bêdzie wrzucony missile
	if(missile_y>terrain[missile_x])
		return true;
	return false;
}
int main
{
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
	
}

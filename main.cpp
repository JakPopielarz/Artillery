#include<iostream>
#include<array>
#include<vector>
#include<math.h>
using namespace std;
bool missile_in_the_air(float missile_x, float missile_y, float terrain[]){ //terrrain to tablica terenu, zmieni� nazwy zmiennych jak b�dzie wrzucony missile
	if(missile_y>terrain[missile_x])
		return true;
	return false;
}
int main
{
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
	
}

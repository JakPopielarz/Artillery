//
// Created by kinga on 5/20/19.
//

#ifndef JIMPPROJEKT_MISSILE_H
#define JIMPPROJEKT_MISSILE_H

#include <vector>

class Missile { //potem mozna przerobic na klase abstrakcyjna
private:
    float starting_x, starting_y; //mozna zamienic tą klase na zaprzyjaźnioną z cannon i od niej pobierać punkt startowy
    float velocity_x, velocity_y;
    //trzeba dodac też wiatr (jako zmienna globalna/ zmienna jakiejs klasy i wtedy jako klasa zaprzyjaziona)
    //jezeli chcemy zrobic w klasie pocisku metody zmieniające pozycje i prędkosc po danym korku czasu
    //float wind_x = 0;
    //float wind_y = 0;
    float radius; //dodatkowe
    float power; //dodatkowe

public:
    Missile(float starting_x, float starting_y, float velocity_x, float velocity_y);
    std::vector<float> get_current_position();
    std::vector<float> get_current_velocity();
    void set_position(float px, float py);
    void set_velocity(float vx, float vy);
    ~Missile()= default;


};


#endif //JIMPPROJEKT_MISSILE_H

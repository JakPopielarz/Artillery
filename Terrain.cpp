#include<iostream>

#include "Terrain.h"

Terrain::Terrain(float radius, float power): _radius(radius), _power(power){
  int x=0;    //numer x, dla którego liczymy y
  for ( auto it = array_of_y_coordinates.begin(); it != array_of_y_coordinates.end(); ++it){      //iteracja po kolejnych elementach tablicy ze współrz. y
    int result = 0;                                 // to bedzie wynik koncowy dla wspolrzednej y
    for(int i = 0; i< v.size(); i += 2){
         result += v[i]*pow(x,v[i+1]);
    }
            
    x++;            //przechodzenie do kolejnego x
    *it = result;   //w array_of_y_coordinates zapisujemy wynik funkcji dla x
   }
}   
    

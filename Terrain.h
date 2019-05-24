#include<iostream>
#include<array>
#include<vector>
#include<math.h>
using namespace std;

const int number_of_x = 20;
//int function[] = {1, 2, 3, 4, 5, 6, 7, 8};
std::vector<int> v = {1,2,3,4,5,6,7,8};

//bedzie wczytywane n = stopien funkcji wielomaniowej
//tworzony wektor bedzie miał 2*n elementow
//for(int i=0; i< 2*n ; i++){
//    cin >> a;
//    v.push_back(a);
//}



class Terrain{

private:
    
    float _radius;
    float _power;
    array<float, number_of_x> array_of_y_coordinates;
    
public:
    Terrain(float radius, float power): _radius(radius), _power(power){}
};

#ifndef ARTILLERY_POINT_H
#define ARTILLERY_POINT_H

#include <iostream>

using namespace std;

class Point {
private:
    float x_;
    float y_;
public:
    Point(): x_{0}, y_{0}{}
    Point(float x, float y): x_{x}, y_{y}{}
    Point(int x, int y): x_{float(x)}, y_{float(y)}{}
    Point(float x, int y): x_{x}, y_{float(y)}{}
    Point(int x, float y): x_{float(x)}, y_{y}{}
    float get_x() { return x_; }
    float get_y() { return y_; }
    void set_x(float x) { x_ = x; }
    void set_y(float y) { y_ = y; }

    Point operator+(Point);
    Point& operator+=(Point);
    friend istream& operator>>(istream &, Point&);
    friend ostream& operator<<(ostream &, Point&);
};


#endif //ARTILLERY_POINT_H

//
// Created by jakub on 12.05.19.
//

#include <iostream>
#include "Point.h"

using namespace std;

Point Point::operator+(Point b) {
    Point result = Point(x_ + b.get_x(), y_ + b.get_y());

    return result;
}

Point& Point::operator+=(Point b) {
    *this = *this + b;

    return *this;
}

istream& operator>>(istream & input, Point& point){
    double x, y;
    input.ignore();
    input >> x;
    input.ignore();
    input >> y;
    input.ignore();

    point.set_x(x);
    point.set_y(y);

    return input;
}

ostream& operator<<(ostream & output, Point& point){
    output << "(" << point.get_x() << "," << point.get_y() << ")";

    return output;
}

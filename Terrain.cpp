#include <iostream>
#include <vector>
#include "Terrain.h"


unsigned int WIDTH = 800;
unsigned int HEIGHT = 600;

Terrain::Terrain(vector<float> points) {
    terrain = sf::ConvexShape(points.size()+3);
    setPoints(points);
    terrain.setFillColor(sf::Color::Transparent);
    terrain.setOutlineColor(sf::Color::Red);
    terrain.setOutlineThickness(-1);
}

void Terrain::setPoints(vector<float>& points) {
    for (size_t i=0; i<terrain.getPointCount()-3; i++) {
        terrain.setPoint(i, sf::Vector2f(i, HEIGHT-points[i]));
    }

    terrain.setPoint(terrain.getPointCount()-3, sf::Vector2f(WIDTH, terrain.getPoint(terrain.getPointCount()-4).y));
    terrain.setPoint(terrain.getPointCount()-2, sf::Vector2f(WIDTH, HEIGHT));
    terrain.setPoint(terrain.getPointCount()-1, sf::Vector2f(0, HEIGHT));
}

void Terrain::draw(sf::RenderWindow& window) {
    window.draw(terrain);
}

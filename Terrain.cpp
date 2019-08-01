#include <iostream>
#include <vector>
#include <math.h>
#include "Terrain.h"


unsigned int WIDTH = 800;
unsigned int HEIGHT = 600;

Terrain::Terrain(float density, sf::Color outline_color) {
    int number_of_vertices = WIDTH*density +1 ;
    sf::VertexArray vertices(sf::LineStrip, number_of_vertices);

    int mod = rand() % (150 - 80 + 1) + 80;
    float phase = ((float) rand()) / (float) 2;
    for(int i=1; i<number_of_vertices; i++) {
        vertices[i].position = sf::Vector2f(i/density, HEIGHT-mod - mod*float(sin(phase*M_1_PI + (i * mod*0.0001))));
        vertices[i].color = outline_color;
        if (vertices[i].position.y > HEIGHT)
            vertices[i].position.y = HEIGHT;
        if (vertices[i].position.y < 0)
            vertices[i].position.y = 0;
    }

    vertices[0].position = sf::Vector2f(0, vertices[1].position.y);
    vertices[0].color = outline_color;

    setVertices(vertices);
}

void Terrain::setVertices(sf::VertexArray &vertices) {
    terrain = vertices;
}

void Terrain::draw(sf::RenderWindow& window) {
    window.draw(terrain);
}

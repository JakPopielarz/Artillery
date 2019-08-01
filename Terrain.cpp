#include <iostream>
#include <vector>
#include "Terrain.h"


unsigned int WIDTH = 800;
unsigned int HEIGHT = 600;

Terrain::Terrain() {
    sf::VertexArray vertices(sf::LineStrip, 800);

    vertices[0].position = sf::Vector2f(0, HEIGHT-70);
    vertices[0].color = sf::Color::Red;
    for(int i=1; i<800; i++) {
        int offset = (rand() % (5 - 1 + 1) + 1) * (rand() % (1 + 1 + 1) - 1);
        vertices[i].position = sf::Vector2f(i, vertices[i - 1].position.y + offset);
        vertices[i].color = sf::Color::Red;
        if (vertices[i].position.y > HEIGHT)
            vertices[i].position.y = HEIGHT - 10;
        if (vertices[i].position.y < 0)
            vertices[i].position.y = 10;
    }
    
    setVertices(vertices);
}

void Terrain::setVertices(sf::VertexArray &vertices) {
    terrain = vertices;
}

void Terrain::draw(sf::RenderWindow& window) {
    window.draw(terrain);
}

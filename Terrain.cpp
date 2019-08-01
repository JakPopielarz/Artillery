#include <iostream>
#include <vector>
#include <math.h>
#include "Terrain.h"


unsigned int WIDTH = 800;
unsigned int HEIGHT = 600;

float get_y(int i, int mod, float phase) {
    return float(HEIGHT-mod*1.5 - mod*float(sin(phase*M_1_PI + (i * mod*0.0001))));
}

sf::VertexArray generate_vertices(float density, sf::Color color) {
    int number = int(WIDTH*density +1);
    sf::VertexArray vertices(sf::LineStrip, number);

    int mod = rand() % (150 - 80 + 1) + 80;
    float phase = ((float) rand()) / (float) 2;
    for(int i=1; i<number; i++) {
        vertices[i].position = sf::Vector2f(i/density, get_y(i, mod, phase));
        vertices[i].color = color;
        if (vertices[i].position.y > HEIGHT)
            vertices[i].position.y = HEIGHT;
        if (vertices[i].position.y < 0)
            vertices[i].position.y = 0;
    }

    vertices[0].position = sf::Vector2f(0, vertices[1].position.y);
    vertices[0].color = color;

    return vertices;
}

Terrain::Terrain(float density, sf::Color outline_color, sf::Color ground_color) {
    sf::VertexArray vertices = generate_vertices(density, outline_color);
    set_vertices(vertices);

    create_texture(ground_color);
    create_sprite();
}

void Terrain::set_vertices(sf::VertexArray &vertices) {
    terrain = vertices;
}

void Terrain::draw(sf::RenderWindow& window) {
    window.draw(sprite);
    window.draw(terrain);
}

void Terrain::create_texture(sf::Color ground_color) {
    texture.create(WIDTH, HEIGHT);

    sf::Image image = texture.copyToImage();
    for (int i=0; i<HEIGHT; i++){
        for (int j=0; j<WIDTH; j++) {
            if (i > terrain[j].position.y)
                image.setPixel(j, i, ground_color);
        }
    }

    texture.loadFromImage(image);
}

void Terrain::create_sprite() {
    sprite.setTexture(texture);
}
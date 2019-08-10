#include "Terrain.h"

float get_y(int i, int mod, float phase) {
    return float(WINDOW_HEIGHT-mod*1.5 - float(mod*sin(phase*M_1_PI + (i * mod*0.0001))));
}

sf::VertexArray generate_vertices(float density, sf::Color color) {
    auto number = size_t(WINDOW_WIDTH*density +1);
    sf::VertexArray vertices(sf::LineStrip, number);

    int mod = rand() % (150 - 80 + 1) + 80;
    float phase = ((float) rand()) / (float) 2;
    for(int i=1; i<number; i++) {
        vertices[i].position = sf::Vector2f(i/density, get_y(i, mod, phase));
        vertices[i].color = color;
        if (vertices[i].position.y > WINDOW_HEIGHT)
            vertices[i].position.y = WINDOW_HEIGHT;
        if (vertices[i].position.y < 0)
            vertices[i].position.y = 0;
    }

    vertices[0].position = sf::Vector2f(0, vertices[1].position.y);
    vertices[0].color = color;

    return vertices;
}

Terrain::Terrain(float density, sf::Color outline_color, sf::Color ground_color) {
    color = ground_color;
    sf::VertexArray vertices = generate_vertices(density, outline_color);
    set_vertices(vertices);

    create_texture();
    create_sprite();
}

void Terrain::set_vertices(sf::VertexArray &vertices) {
    terrain = vertices;
}

void Terrain::draw(sf::RenderWindow& window) {
    window.draw(sprite);
    window.draw(terrain);
}

void Terrain::create_texture() {
    texture.create(WINDOW_WIDTH, WINDOW_HEIGHT);

    sf::Image image;
    image.create(WINDOW_WIDTH, WINDOW_HEIGHT, sf::Color(0,0,0,0));
    for (unsigned int i=0; i<WINDOW_HEIGHT; i++){
        for (unsigned int j=0; j<WINDOW_WIDTH; j++) {
            if (i > terrain[j].position.y)
                image.setPixel(j, i, color);
        }
    }

    texture.loadFromImage(image);
}

void Terrain::create_sprite() {
    sprite.setTexture(texture);
}

void Terrain::destroy(sf::Vector2f location, float radius) {
    for (int i=int(fmax(location.x-radius, 0)); i<=fmin(location.x+radius, WINDOW_WIDTH); i++) {
        float new_y = terrain[i].position.y + location.y - terrain[i].position.y +
                + sqrt(radius * radius - (i - location.x) * (i - location.x));
        terrain[i].position.y = fmax(new_y, terrain[i].position.y);
    }

    create_texture();
    create_sprite();
}
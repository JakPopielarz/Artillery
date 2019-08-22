#ifndef ARTILLERY_TERRAIN_H
#define ARTILLERY_TERRAIN_H

#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "Constants.h"

class Terrain {
private:
    sf::VertexArray terrain;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Color color;

    void create_texture();
    void create_sprite();
public:
    explicit Terrain(float density=1, sf::Color outline_color=sf::Color::Black, sf::Color ground_color=sf::Color(87, 158, 21));
    void set_vertices(sf::VertexArray &vertices);
    void draw(sf::RenderWindow& window);
    void destroy(sf::Vector2f location, float radius);
    sf::VertexArray get_vertices() { return terrain; }
};

#endif //ARTILLERY_TERRAIN_H
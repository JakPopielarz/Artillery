#include <SFML/Graphics.hpp>
#include "Point.h"

using namespace std;

class Terrain{
private:
    sf::VertexArray terrain;
    sf::Texture texture;
    sf::Sprite sprite;

    void create_texture(sf::Color ground_color);
    void create_sprite();
public:
    Terrain(float density=1, sf::Color outline_color=sf::Color::Black, sf::Color ground_color=sf::Color(87, 158, 21));
    void set_vertices(sf::VertexArray &vertices);
    void draw(sf::RenderWindow& window);
};

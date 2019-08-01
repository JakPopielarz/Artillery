#include <SFML/Graphics.hpp>
#include "Point.h"

using namespace std;

class Terrain{
private:
    sf::VertexArray terrain;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Color color;

    void create_texture();
    void create_sprite();
public:
    Terrain(float density=1, sf::Color outline_color=sf::Color::Black, sf::Color ground_color=sf::Color(87, 158, 21));
    void set_vertices(sf::VertexArray &vertices);
    void draw(sf::RenderWindow& window);
    void destroy(sf::Vector2f location, float radius);
};

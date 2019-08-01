#include <SFML/Graphics.hpp>
#include "Point.h"

using namespace std;

class Terrain{
private:
    sf::VertexArray terrain;
public:
    explicit Terrain(float density=1, sf::Color outline_colour=sf::Color::Black);
    void setVertices(sf::VertexArray &vertices);
    void draw(sf::RenderWindow& window);
};

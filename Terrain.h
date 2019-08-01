#include <SFML/Graphics.hpp>
#include "Point.h"

using namespace std;

class Terrain{
private:
    sf::VertexArray terrain;
public:
    Terrain();
    void setVertices(sf::VertexArray &vertices);
    void draw(sf::RenderWindow& window);
};

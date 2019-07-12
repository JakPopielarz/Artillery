#include <SFML/Graphics.hpp>
using namespace std;

class Terrain{
private:
    sf::ConvexShape terrain;
public:
    Terrain(size_t number_of_points, float points[]);
    void setPoints(float points[]);
    void draw(sf::RenderWindow& window);
};

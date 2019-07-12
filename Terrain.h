#include <SFML/Graphics.hpp>
using namespace std;

class Terrain{
private:
    sf::ConvexShape terrain;
public:
    Terrain(size_t number_of_points, vector<float> points);
    void setPoints(vector<float> points);
    void draw(sf::RenderWindow& window);
};

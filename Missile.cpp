//
// Created by kinga on 5/20/19.
//

#include "Missile.h"
using namespace std;

Missile::Missile(float starting_x, float starting_y, float starting_velocity, float alpha, float wind_x, float wind_y, float size, sf::Color color) {
    velocity = sf::Vector2f(cos(alpha)*starting_velocity+wind_x, sin(alpha)*starting_velocity+wind_y);
    missile.setRadius(size);
    missile.setPosition(starting_x, starting_y);
    missile.setFillColor(color);
}

Missile::Missile(sf::Vector2f starting_position, sf::Vector2f starting_velocity, sf::Vector2f wind, float size, sf::Color color) {
    velocity = starting_velocity + wind;
    missile.setRadius(size);
    missile.setPosition(starting_position);
    missile.setFillColor(color);
}

void Missile::draw(sf::RenderWindow &window) {
    window.draw(missile);
}

void Missile::move_over(Terrain& terrain) {
    sf::Vector2f new_position = sf::Vector2f(missile.getPosition().x+velocity.x/10, missile.getPosition().y-velocity.y/10);
    missile.setPosition(new_position);
    velocity.y -= GRAVITY_SPEED;

    flying = check_flying_over(terrain);
    if (!flying) {
        terrain.destroy(missile.getPosition(), missile.getRadius()*10);
        reset();
    }
}

bool Missile::check_flying_over(Terrain &terrain) {
    sf::VertexArray vertices = terrain.get_vertices();

    auto index = size_t(missile.getPosition().x);
    return (missile.getPosition().y < vertices[index].position.y);
}

void Missile::reset() {
    velocity = sf::Vector2f(0,0);
    missile.setPosition(-1000, -1000);
}

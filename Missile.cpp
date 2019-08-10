//
// Created by kinga on 5/20/19.
//

#include "Missile.h"

Missile::Missile() {
    wind_strength = 0;
    velocity = sf::Vector2f(0,0);
    missile.setRadius(2);
    missile.setPosition(sf::Vector2f(-1000, - 1000));
    missile.setFillColor(sf::Color::Black);
}

Missile::Missile(sf::Vector2f starting_position, sf::Vector2f starting_velocity, float wind, float size, sf::Color color) {
    wind_strength = wind;
    velocity = starting_velocity;
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
    velocity.x += wind_strength/1000;

    flying = check_flying_over(terrain);
}

bool Missile::check_flying_over(Terrain &terrain) {
    sf::VertexArray vertices = terrain.get_vertices();

    auto index = size_t(missile.getPosition().x);
    return (missile.getPosition().y < vertices[index].position.y &&
            missile.getPosition().y > 0 && missile.getPosition().y < WINDOW_HEIGHT);
}

void Missile::reset() {
    velocity = sf::Vector2f(0,0);
    missile.setPosition(-1000, -1000);
}

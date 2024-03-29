//
// Created by kinga on 5/20/19.
//

#include "Missile.h"

Missile::Missile() {
    wind_strength = 0;
    velocity = sf::Vector2f(0,0);
    missile.setRadius(2);
    missile.setOrigin(missile.getRadius(), missile.getRadius());
    missile.setPosition(sf::Vector2f(-1000, - 1000));
    missile.setFillColor(sf::Color::Black);
}

void Missile::draw(sf::RenderWindow &window) {
    window.draw(missile);
}

void Missile::move_over(Terrain &terrain, vector<Cannon*>& cannons) {
    sf::Vector2f new_position = sf::Vector2f(missile.getPosition().x+velocity.x/10, missile.getPosition().y-velocity.y/10);
    missile.setPosition(new_position);
    velocity.y -= GRAVITY_SPEED;
    velocity.x += wind_strength*WIND_IMPACT_ON_FLIGHT;

    bool collided;
    flying = check_flying_over(terrain);
    collided = check_collision_with(cannons);
    if (collided)
        flying = false;
}

bool Missile::check_flying_over(Terrain &terrain) {
    sf::VertexArray vertices = terrain.get_vertices();

    auto index = size_t(missile.getPosition().x);
    return (missile.getPosition().y < vertices[index].position.y &&
            missile.getPosition().y > 0 && missile.getPosition().y < WINDOW_HEIGHT);
}

bool Missile::check_collision_with(vector<Cannon*>& cannons) {
    for (auto cannon : cannons) {
        if (in_cannon(cannon))
            return true;
    }
    return  false;
}

bool Missile::in_cannon(Cannon *cannon) {
    sf::Vector2f position = missile.getPosition();
    return (position.x > cannon->get_position().x && position.x < cannon->get_position().x+CANNON_SIZE.x &&
            position.y > cannon->get_position().y && position.y < cannon->get_position().y+CANNON_SIZE.y);
}

void Missile::reset() {
    velocity = sf::Vector2f(0,0);
    missile.setPosition(-1000, -1000);
    wind_strength = 0;
    flying = false;
}

void Missile::explode(sf::RenderWindow& window) {
    float starting_radius = missile.getRadius();
    sf::Vector2f explosion_position = missile.getPosition();
    missile.setFillColor(sf::Color(255, 71, 26));

    while (missile.getRadius() < starting_radius * 10 && on_screen()) {
        missile.setRadius(missile.getRadius() + MISSILE_EXPLOSION_INCREMENT);
        missile.setPosition(explosion_position.x-missile.getRadius(), explosion_position.y-missile.getRadius());
        draw(window);
        window.display();
    }

    missile.setRadius(starting_radius);
    missile.setPosition(explosion_position);
}

bool Missile::on_screen() {
    return (missile.getPosition().x > 0 && missile.getPosition().x < WINDOW_WIDTH &&
            missile.getPosition().y > 0 && missile.getPosition().y < WINDOW_HEIGHT);
}

void Missile::set_parameters(map<string, sf::Vector2f>& parameters, sf::Color color) {
    set_position(parameters["coords"]);
    set_velocity(parameters["velocity"]);
    set_wind(parameters["wind"].x);
    set_color(color);
    missile.setRadius(parameters["radius"].x);
    explosion_coefficient = parameters["explosion_coefficient"].x;
    flying = true;
}

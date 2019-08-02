//
// Created by jakub on 12.05.19.
//

#include "Cannon.h"

Cannon::Cannon(float position_x, float position_y, sf::Color colour) {
    health_points_ = 100;
    cannon_angle_ = 90;
    width = 20;
    height = 10;
    fall_velocity = 0;

    cannon.setSize(sf::Vector2f(width, height));
    cannon.setFillColor(colour);
    cannon.setOutlineThickness(-1.f);
    cannon.setOutlineColor(sf::Color::Black);
    cannon.setPosition(position_x, position_y - height);

    barrel.setSize(sf::Vector2f(12, 1));
    barrel.setFillColor(sf::Color::Black);
    barrel.setPosition(position_x + width / 2, position_y - height / 2);
    barrel.rotate(-cannon_angle_);
}

void Cannon::draw(sf::RenderWindow& window) {
    window.draw(cannon);
    window.draw(barrel);
}

Missile Cannon::shoot(float force, float wind[]) {
//    return Missile(position_.get_x()+width/2, position_.get_y()-height/2, force, cannon_angle_, wind[0], wind[1]);
}

bool Cannon::is_on(Terrain terrain) {
    sf::VertexArray vertices = terrain.get_vertices();
    for (float i=cannon.getPosition().x; i<=cannon.getPosition().x+width; i++){
        if (cannon.getPosition().y+height >= vertices[i].position.y)
            return true;
    }
    return false;
}

void Cannon::move(side side, float amount) {
    sf::Vector2f displacement = side.get_vector() * amount;

    cannon.setPosition(cannon.getPosition().x + displacement.x, cannon.getPosition().y + displacement.y);
    barrel.setPosition(barrel.getPosition().x + displacement.x, barrel.getPosition().y + displacement.y);
}

void Cannon::move_on(Terrain terrain, side side, float amount) {
    sf::Vector2f displacement = side.get_vector() * amount;
    sf::VertexArray vertices = terrain.get_vertices();

    float offset = 0;
    size_t index;
    if (side.direction == "left")
        index = size_t(cannon.getPosition().x+displacement.x);
    else
        index = size_t(cannon.getPosition().x+displacement.x+width);

    if (cannon.getPosition().y+height <= vertices[index].position.y+MAX_MOVEMENT_ELEVATION) {
        cannon.setPosition(cannon.getPosition().x + displacement.x, cannon.getPosition().y + displacement.y);

        if (side.direction == "right")
            offset = width;

        if (cannon.getPosition().y+height > vertices[cannon.getPosition().x+offset].position.y)
            cannon.setPosition(cannon.getPosition().x, vertices[cannon.getPosition().x+offset].position.y-height);

        barrel.setPosition(barrel.getPosition().x + displacement.x, cannon.getPosition().y+height/2);
    }
}

void Cannon::fall() {
    move(side("down"), fall_velocity);
    if (fall_velocity < CANNON_MAX_FALL_VELOCITY)
        fall_velocity += CANNON_FALL_VELOCITY_INCREMENT;
}
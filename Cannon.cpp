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

Missile Cannon::shoot() {
    sf::Vector2f missile_velocity;
    float rotation_degrees = 360-barrel.getRotation();
    float rotation_radians = rotation_degrees * float(M_PI/180);

    cout << (360-barrel.getRotation())* float(M_PI/180) << endl;
    missile_velocity.x = cos(rotation_radians) * 10;
    missile_velocity.y = sin(rotation_radians) * 10;

    cout << missile_velocity.x << ", " << missile_velocity.y << endl;
    cout << cos(90* float(M_PI/180)) << ", " << sin(90* float(M_PI/180)) << endl;

    Missile missile = Missile(barrel.getPosition(), missile_velocity);
    return missile;
}

bool Cannon::is_on(Terrain terrain) {
    sf::VertexArray vertices = terrain.get_vertices();
    for (float i=cannon.getPosition().x; i<=cannon.getPosition().x+width; i++){
        if (cannon.getPosition().y+height >= vertices[i].position.y)
            return true;
    }
    return false;
}

void Cannon::move_on(Terrain terrain, side side, float amount) {
    sf::Vector2f displacement = side.get_vector() * amount;
    sf::VertexArray vertices = terrain.get_vertices();

    float offset = 0;
    size_t index;
    if (side.direction == "right")
        index = size_t(cannon.getPosition().x+displacement.x+width);
    else
        index = size_t(cannon.getPosition().x+displacement.x);

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

    cannon.setPosition(cannon.getPosition().x, cannon.getPosition().y + fall_velocity);
    barrel.setPosition(barrel.getPosition().x, barrel.getPosition().y + fall_velocity);
    if (fall_velocity < MAX_FALL_VELOCITY)
        fall_velocity += GRAVITY_SPEED;
}

void Cannon::rotate_barrel(side side) {
    if (side.direction == "up" and barrel.getRotation() > BARREL_MIN_ROTATION)
        barrel.rotate(side.vector.y*BARREL_ROTATION_AMOUNT);
    else if (side.direction == "down") {
        barrel.rotate(side.vector.y * BARREL_ROTATION_AMOUNT);
        if (barrel.getRotation() < BARREL_MIN_ROTATION)
            barrel.setRotation(BARREL_MAX_ROTATION-0.1f);
    }
}

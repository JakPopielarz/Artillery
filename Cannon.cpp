//
// Created by jakub on 12.05.19.
//

#include "Cannon.h"

float min(float float1, float float2) {
    if (float1 < float2)
        return float1;
    else
        return float2;
}

float max(float float1, float float2) {
    if (float1 > float2)
        return float1;
    else
        return float2;
}

float distance(sf::Vector2f point1, sf::Vector2f point2) {
    auto distance = float(sqrt(pow(point1.x-point2.x, 2) + pow(point1.y-point2.y, 2)));
    return distance;
}

Cannon::Cannon(sf::Vector2f position, sf::Color colour, string nick) {
    name = move(nick);
    fall_velocity = 0;
    shot_strength = 50;

    cannon.setSize(sf::Vector2f(CANNON_SIZE.x, CANNON_SIZE.y));
    cannon.setFillColor(colour);
    cannon.setOutlineThickness(-1.f);
    cannon.setOutlineColor(sf::Color::Black);
    cannon.setPosition(position.x, position.y - cannon.getSize().y);

    barrel.setSize(sf::Vector2f(12, 1));
    barrel.setFillColor(sf::Color::Black);
    barrel.setPosition(position.x + cannon.getSize().x / 2, position.y - cannon.getSize().y / 2);
    barrel.rotate(-90);

    hit_points_int = 100;
}

void Cannon::draw(sf::RenderWindow& window) {
    window.draw(cannon);
    window.draw(barrel);
}

void Cannon::change_shot_strength(float amount) {
    if (amount < 0)
        shot_strength = max(shot_strength+amount, 0);
    else if (amount > 0)
        shot_strength = min(shot_strength+amount, 100);
}

vector<sf::Vector2f> Cannon::shoot() {
    sf::Vector2f missile_velocity;
    float rotation_degrees = 360-barrel.getRotation();
    float rotation_radians = rotation_degrees * float(M_PI/180);

    missile_velocity.x = cos(rotation_radians) * MAX_SHOT_STRENGTH * shot_strength / 100;
    missile_velocity.y = sin(rotation_radians) * MAX_SHOT_STRENGTH * shot_strength / 100;

    sf::Vector2f missile_coords;
    missile_coords.x = cos(rotation_radians) * barrel.getSize().x + barrel.getPosition().x;
    missile_coords.y = -sin(rotation_radians) * barrel.getSize().x + barrel.getPosition().y;

    vector<sf::Vector2f> missile_params;
    missile_params.emplace_back(missile_coords);
    missile_params.emplace_back(missile_velocity);
    return missile_params;
}

bool Cannon::is_on(Terrain terrain) {
    sf::VertexArray vertices = terrain.get_vertices();
    for (int i=cannon.getPosition().x; i<=int(cannon.getPosition().x+cannon.getSize().x); i++){
        if (cannon.getPosition().y+cannon.getSize().y >= vertices[i].position.y)
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
        index = size_t(cannon.getPosition().x+displacement.x+cannon.getSize().x);
    else
        index = size_t(cannon.getPosition().x+displacement.x);

    if (cannon.getPosition().y+cannon.getSize().y <= vertices[index].position.y+MAX_MOVEMENT_ELEVATION) {
        cannon.setPosition(cannon.getPosition().x + displacement.x, cannon.getPosition().y + displacement.y);

        if (side.direction == "right")
            offset = cannon.getSize().x;

        if (cannon.getPosition().y+cannon.getSize().y > vertices[cannon.getPosition().x+offset].position.y)
            cannon.setPosition(cannon.getPosition().x, vertices[cannon.getPosition().x+offset].position.y-cannon.getSize().y);

        barrel.setPosition(barrel.getPosition().x + displacement.x, cannon.getPosition().y+cannon.getSize().y/2);
    }
}

void Cannon::fall() {
    cannon.setPosition(cannon.getPosition().x, cannon.getPosition().y + fall_velocity);
    barrel.setPosition(barrel.getPosition().x, barrel.getPosition().y + fall_velocity);
    if (fall_velocity < MAX_FALL_VELOCITY)
        fall_velocity += GRAVITY_SPEED;

    if (cannon.getPosition().y > WINDOW_HEIGHT)
        destroy();
}

void Cannon::rotate_barrel(const side& side) {
    if (side.direction == "up" and barrel.getRotation() > BARREL_MIN_ROTATION)
        barrel.rotate(side.vector.y*BARREL_ROTATION_AMOUNT);
    else if (side.direction == "down") {
        barrel.rotate(side.vector.y * BARREL_ROTATION_AMOUNT);
        if (barrel.getRotation() < BARREL_MIN_ROTATION)
            barrel.setRotation(BARREL_MAX_ROTATION-0.1f);
    }
}

bool Cannon::in_explosion(sf::Vector2f location, float radius) {
    sf::Vector2f cannon_center = cannon.getPosition();
    cannon_center.x += cannon.getSize().x/2;
    cannon_center.y -= cannon.getSize().y/2;
    
    return (distance(cannon_center, location) <= radius + cannon.getSize().y/2);
}

void Cannon::lower_hp(int amount) {
    hit_points_int -= amount;

    if (hit_points_int < 0)
        hit_points_int = 0;
}

sf::Vector2f Cannon::destroy() {
    hit_points_int = 0;
    sf::Vector2f cannon_center = cannon.getPosition();
    cannon_center.x += cannon.getSize().x/2;
    cannon_center.y -= cannon.getSize().y/2;
    cannon.setPosition(-1000, -1000);
    barrel.setPosition(-1000, -1000);

    return cannon_center;
}

bool Cannon::out_of_screen() {
    return (cannon.getPosition().x < -WINDOW_MARGIN/2 || cannon.getPosition().x+CANNON_SIZE.x > WINDOW_WIDTH+WINDOW_MARGIN/2 ||
            cannon.getPosition().y < -WINDOW_MARGIN/2 || cannon.getPosition().y+CANNON_SIZE.y > WINDOW_HEIGHT+WINDOW_MARGIN/2);
}

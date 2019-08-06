//
// Created by jakub on 12.05.19.
//

#include "Cannon.h"

float distance(sf::Vector2f point1, sf::Vector2f point2) {
    auto distance = float(sqrt(pow(point1.x-point2.x, 2) + pow(point1.y-point2.y, 2)));
    return distance;
}

Cannon::Cannon(float position_x, float position_y, sf::Color colour) {
    fall_velocity = 0;

    cannon.setSize(sf::Vector2f(CANNON_SIZE.x, CANNON_SIZE.y));
    cannon.setFillColor(colour);
    cannon.setOutlineThickness(-1.f);
    cannon.setOutlineColor(sf::Color::Black);
    cannon.setPosition(position_x, position_y - cannon.getSize().y);

    barrel.setSize(sf::Vector2f(12, 1));
    barrel.setFillColor(sf::Color::Black);
    barrel.setPosition(position_x + cannon.getSize().x / 2, position_y - cannon.getSize().y / 2);
    barrel.rotate(-90);

    hit_points_int = 100;
    if (!font.loadFromFile("../Resources/Fonts/ALoveofThunder.ttf")) {
        cout << "Error loading font from file" << endl;
        system("pause");
    }
    hit_points.setFont(font);
    string hp_string = "HP: " + to_string(hit_points_int);
    hit_points.setString(hp_string);
    hit_points.setPosition(10, 10);
    hit_points.setFillColor(colour);
}

void Cannon::draw(sf::RenderWindow& window) {
    window.draw(cannon);
    window.draw(barrel);
}

void Cannon::display_hit_points(sf::RenderWindow &window) {
    string hp_string = "HP: " + to_string(hit_points_int);
    hit_points.setString(hp_string);
    window.draw(hit_points);
}

Missile Cannon::shoot() {
    sf::Vector2f missile_velocity;
    float rotation_degrees = 360-barrel.getRotation();
    float rotation_radians = rotation_degrees * float(M_PI/180);

    missile_velocity.x = cos(rotation_radians) * 10;
    missile_velocity.y = sin(rotation_radians) * 10;

    Missile missile = Missile(barrel.getPosition(), missile_velocity);
    return missile;
}

bool Cannon::is_on(Terrain terrain) {
    sf::VertexArray vertices = terrain.get_vertices();
    for (float i=cannon.getPosition().x; i<=cannon.getPosition().x+cannon.getSize().x; i++){
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

void Cannon::rotate_barrel(side side) {
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

Missile Cannon::destroy() {
    hit_points_int = 0;
    sf::Vector2f cannon_center = cannon.getPosition();
    cannon_center.x += cannon.getSize().x/2;
    cannon_center.y -= cannon.getSize().y/2;
    cannon.setPosition(-1000, -1000);
    barrel.setPosition(-1000, -1000);

    Missile phantom = Missile(cannon_center, sf::Vector2f(0,0), sf::Vector2f(0,0), CANNON_EXPLOSION_SIZE, sf::Color::Transparent);
    return phantom;
}

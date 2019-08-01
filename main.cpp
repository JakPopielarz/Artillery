#include <iostream>
#include <math.h>
#include <string>
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Point.h"
#include "Cannon.h"
#include "Terrain.h"

using namespace std;

vector<string> split(string& str) {
    vector<string> split_vc = vector<string>();
    size_t pos;
    while(!str.empty()) {
        pos = str.find(" ");
        split_vc.emplace_back(str.substr(0, pos));
        str.erase(0, pos);
        if (str.find(" ") == 0)
            str.erase(0, 1);
    }
    return split_vc;
}

vector<float> values(string function) {
    vector<string> f_split_str = split(function);
    size_t x_pos;
    string x_str_exp;
    float x_exp=0, coeff=0, value=0, x=0;
    vector<float> values = vector<float>();

    for (int k=0; k<800; k+=2) {
        x = float(k)/100.0f;
        for (string i: f_split_str) {
            x_pos = i.find("x");

            if (x_pos != string::npos) {
                x_str_exp = i.substr(x_pos + 2);
                i.erase(x_pos);
                x_exp = stof(x_str_exp);
            } else {
                x_exp = 0;
            }

            coeff = stof(i);
            value += coeff * float(pow(x, x_exp)) + 1;
        }
        values.push_back(value);
    }
    return values;
}

int main() {
    srand(time(NULL));

    vector<float> terrain_points = vector<float>(800);

    terrain_points[0] = 70;
    for(int i=1; i<800; i++) {
        int offset = (rand() % (5 - 1 + 1) + 1) * (rand() % (1 + 1 + 1) - 1);
        terrain_points[i] = terrain_points[i - 1] + offset;
        if (terrain_points[i] > WINDOW_HEIGHT)
            terrain_points[i] = WINDOW_HEIGHT - 10;
        if (terrain_points[i] < 0)
            terrain_points[i] = 10;
    }


    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Artillery", sf::Style::Default, settings);

    Terrain terrain = Terrain(terrain_points);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(139, 194, 239));
        terrain.draw(window);
        window.display();
    }

    return 0;
}
//
// Created by jakub on 07.08.19.
//

#include "EndScreen.h"

using namespace std;

EndScreen::EndScreen(const string& winner, sf::Color color) {
    if (!font.loadFromFile("../Resources/Fonts/ALoveofThunder.ttf")) {
        cout << "Error loading font from file" << endl;
        system("pause");
    }
    header.setFont(font);
    header.setFillColor(sf::Color::Black);
    header.setString("Game Over!\n   Winner:");
    header.setOrigin(header.getGlobalBounds().left+header.getGlobalBounds().width/2,
                     header.getGlobalBounds().top+header.getGlobalBounds().height);
    header.setPosition(WINDOW_WIDTH/2.f, WINDOW_HEIGHT/2.f);

    follow_up.setFont(font);
    follow_up.setFillColor(color);
    follow_up.setString(winner);
    follow_up.setOrigin(follow_up.getGlobalBounds().left+follow_up.getGlobalBounds().width/2,
                        follow_up.getGlobalBounds().top);
    follow_up.setPosition(WINDOW_WIDTH/2.f, WINDOW_HEIGHT/2.f);
}

void EndScreen::draw(sf::RenderWindow &window) {
    window.draw(header);
    window.draw(follow_up);
}

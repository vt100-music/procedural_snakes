#include <iostream>
#include <SFML/Graphics.hpp>
#include "segment.h"
#include "creature.h"

int main() {
    // First thing, whatever boiler plate with need for SMFT to draw stuff
    uint width = 2000;
    uint height = 1000;
    sf::Vector2u windowSize = {width, height};
    sf::RenderWindow window(sf::VideoMode(windowSize), "Psnakes", sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    Creature creature_1(sf::Vector2u(width/2, height/2), 30, 15, window);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent()) {
            // Window closed or escape key pressed: exit
            if (event->is<sf::Event::Closed>() ||
                (event->is<sf::Event::KeyPressed>() &&
                 event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape))
            {
                window.close();
                break;
            }
        }
        window.clear();
        creature_1.update(window);
        creature_1.display(window);
        window.display();

    }
    return 0;
}
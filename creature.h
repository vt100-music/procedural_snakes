//
// Created by Carl Cosmos on 9/9/25.
//
#ifndef CREATURE_H
#define CREATURE_H

#include <vector>
#include <SFML/Graphics.hpp>

class Segment;

void drawArc(sf::RenderWindow& window, sf::Vector2f center, float radius, float startAngleRad, float endAngleRad, int segments, float rotation_radians, sf::Color color);

class Creature {
    // TODO - we'll come back and make the body length variable later.
    std::vector<Segment> body;
    int body_length = 20;
    int speed = 4;

public:
    Creature(sf::Vector2u creature_location, float radius, float distance, sf::RenderWindow &window);
    void display(sf::RenderWindow &window);
    void update(sf::RenderWindow &window);
    void drawFin(sf::RenderWindow &window);
};



#endif //CREATURE_H

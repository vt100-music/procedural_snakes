//
// Created by Carl Cosmos on 9/9/25.
//

#include "creature.h"

#include "segment.h"
#include <SFML/Graphics.hpp>
#include <math.h>

Creature::Creature(sf::Vector2u creature_location, float radius, float distance, sf::RenderWindow &window) {

    sf::Color hue = sf::Color::Green;

    for (int i = 0; i <= body_length; i++) {
        float current_radius = radius - i*(radius/(body_length-1));
        hue.r += 255/body_length;
        hue.b += 255/body_length;
        hue.g -= 255/body_length;
        body.push_back(Segment(creature_location.x - i*radius,
            creature_location.y,
            0,
            current_radius,
            current_radius,
            hue,
            window));
    }
}

void Creature::display(sf::RenderWindow &window) {
    // For drawing the individual segments
    // for (int i = 0; i <= body_length; i++) {
    //      body[i].draw();
    // }

    drawArc(window,
        sf::Vector2f(body[0].x, body[0].y),
        body[0].radius,
        -0.5*M_PI,
        0.5*M_PI,
        10,
        body[0].angle_radians,
        sf::Color::Green);

    // For the outline version, draw an arc for the head.  arc function ripped off from ai since sfml
    // doesn't provide one like processing does
    float x1,y1,x2,y2;
    for (int i = 0; i <= body_length - 1; i++) {
        body[i].draw();
        // Side 1
        x1 = body[i].x + body[i].radius*cos(body[i].angle_radians - .5*M_PI);
        y1 = body[i].y + body[i].radius*sin(body[i].angle_radians - .5*M_PI);
        x2 = body[i+1].x + body[i+1].radius*cos(body[i+1].angle_radians - .5*M_PI);
        y2 = body[i+1].y + body[i+1].radius*sin(body[i+1].angle_radians - .5*M_PI);

        // Draw line segments using the vertexarray pattern
        sf::VertexArray line1(sf::PrimitiveType::Lines, 2);
        line1[0].position = sf::Vector2f(x1, y1);
        line1[0].color = body[i].hue;
        line1[1].position = sf::Vector2f(x2, y2);
        line1[1].color = body[i].hue;

        window.draw(line1);
        // Side 1
        x1 = body[i].x + body[i].radius*cos(body[i].angle_radians + .5*M_PI);
        y1 = body[i].y + body[i].radius*sin(body[i].angle_radians + .5*M_PI);
        x2 = body[i+1].x + body[i+1].radius*cos(body[i+1].angle_radians + .5*M_PI);
        y2 = body[i+1].y + body[i+1].radius*sin(body[i+1].angle_radians + .5*M_PI);

        // Draw line segments using the vertexarray pattern
        sf::VertexArray line2(sf::PrimitiveType::Lines, 2);
        line2[0].position = sf::Vector2f(x1, y1);
        line2[0].color = sf::Color::Green;
        line2[1].position = sf::Vector2f(x2, y2);
        line2[1].color = sf::Color::Green;

        window.draw(line2);
    }
    drawFin(window);
}

void Creature::update(sf::RenderWindow &window) {
    // First we move the head, then we use it to seed the rest of the snake
    // XXX - c++ noob reminder - if you don't make this a reference, it will construct a new segment
    // and you'll be operating on a copy.
    Segment& head = body[0];
    // get mouse position relative to the window
    sf::Vector2i mousePosWindow = sf::Mouse::getPosition(window);
    float new_angle_radians = atan2(mousePosWindow.y-head.y, mousePosWindow.x-head.x);
    float delta = new_angle_radians - head.angle_radians;
    // TODO This here is to with radian math that can get weird and make the snake veer off course (from tutorial)
    // basically its to clamp the delta within a single circle.
    while (delta < -M_PI) {
        delta += 2*M_PI;
    }
    while (delta > M_PI) {
        delta -= 2*M_PI;
    }
    // Modify the constant here to make the snake turn faster.  If snake turns too fast it will kink.
    head.angle_radians += 0.03*delta;

    head.x += speed*cos(head.angle_radians);
    head.y += speed*sin(head.angle_radians);
    // Update the rest of the snake down the chain.
    for (int i = 1; i <= body_length; i++) {
        body[i].update(body[i-1]);
    }
}

void drawArc(sf::RenderWindow& window, sf::Vector2f center, float radius, float startAngleRad, float endAngleRad, int segments, float rotation_radians, sf::Color color)
{
    sf::VertexArray arc(sf::PrimitiveType::LineStrip, segments + 1);

    float angleStep = (endAngleRad - startAngleRad) / segments;

    for (int i = 0; i <= segments; ++i)
    {
        float currentAngle = startAngleRad + i * angleStep;
        float x = center.x + radius * std::cos(currentAngle);
        float y = center.y + radius * std::sin(currentAngle);
        arc[i] = sf::Vertex(sf::Vector2f(x, y), color);
    }
    sf::Transform t;
    t.rotate(sf::radians(rotation_radians), center);

    window.draw(arc, t);
}

void Creature::drawFin(sf::RenderWindow& window) {
    for (int i = 2; i < 5; i++) {
        sf::VertexArray line(sf::PrimitiveType::Lines, 2);
        line[0].position = sf::Vector2f(body[i].x, body[i].y);
        line[1].position = sf::Vector2f(body[i].x + (-3*body[i].distance), body[i].y);
        line[0].color = sf::Color::Yellow;
        line[1].color = sf::Color::Yellow;
        sf::Transform t;
        t.rotate(sf::radians(body[i].angle_radians), sf::Vector2f(body[i].x, body[i].y));
        window.draw(line, t);
    }
}
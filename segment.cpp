//
// Created by Carl Cosmos on 9/9/25.
//

#include <SFML/Graphics.hpp>
#include "segment.h"

void Segment::draw() {
    // Calls from procedural
    // pushMatrix() -- this is some kind of coordinate system isolation
    // translate(x,y) -- this makes 0,0 at x,y
    //rotate(angle) -- rotate uh
    //circle(0, 0, 2*radius ) -- i think this draws the circle
    //line(0, 0, distance, 0) -- draws the line of the circle
    //popMatrix() -- returns to the og coordinate system
    sf::CircleShape circle;
    circle.setRadius(radius);
    circle.setOrigin(sf::Vector2f(radius, radius));
    circle.setPosition({x, y});
    circle.setFillColor(hue);
    circle.rotate(sf::radians(angle_radians));

    window.draw(circle);

    // // TODO - line is a debugging thing, add a flag?
    // sf::RectangleShape line({radius, 2.0});
    // line.setPosition({x, y});
    // line.rotate(sf::radians(angle_radians));
    // line.setFillColor(sf::Color::Red);
    // window.draw(line);
}

void Segment::update(Segment PrevSegment) {
    // We can form a right triangle with any two points in a 2d space.  That's the magic of this movement
    // All we need to understand in order to get from point a to point b is
    // the distance between those two points and the angle
    // The distance is the triangles hypotenuse
    // And then we can use the arc tan to get the local angle.
    angle_radians =  atan2(PrevSegment.y - y, PrevSegment.x - x);
    float distance_to_prev = sqrt(pow(PrevSegment.x-x,2) + pow(PrevSegment.y-y,2));
    if (distance_to_prev > distance) {
        // delta is how far we have to move to maintain distance relative to the previous segment
        float delta = distance_to_prev - distance;
        x += delta * cos(angle_radians);
        y += delta * sin(angle_radians);
    }

}


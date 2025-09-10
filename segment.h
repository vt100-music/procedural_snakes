//
// Created by Carl Cosmos on 9/9/25.
//

#ifndef SEGMENT_H
#define SEGMENT_H



class Segment {

public:
    float x;
    float y;
    float angle_radians;
    float distance;
    float radius;
    sf::Color hue;
    sf::RenderWindow& window;
    // Constructor
    Segment(float x, float y, float angle, float distance, float radius, sf::Color hue, sf::RenderWindow& window)
    : x(x), y(y), angle_radians(angle), distance(distance), radius(radius), hue(hue), window(window) {};

    void draw();
    void update(Segment PrevSegment);

};



#endif //SEGMENT_H

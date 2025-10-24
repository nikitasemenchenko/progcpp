#pragma once
#include "Painter.h"
#include "Point.h"
#include "Velocity.h"

class Ball {
private: 
    Velocity ballVelo;
    Point ballCenter;
    double ballRad;
    Color ballColor;
    bool isCollidable;
public:
    Ball(Point center, Velocity velocity, double radius, Color color, bool collision);
    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;
    double getRadius() const;
    double getMass() const;
    Color getColor() const;
    bool getCollision() const;
};

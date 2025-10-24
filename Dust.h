#pragma once

#include "Point.h"
#include "Color.h"
#include "Painter.h"



class Dust {
    private:
        Point dustVelo;
        Point dustCenter;
        double dustRad;
        Color dustColor;
        double lifeTime;

    public:
        Dust(Point center, Point velocity, double radius, Color color, double lifetime);
        void update(double tick);
        bool isDead() const;
        void draw(Painter& painter) const;
};
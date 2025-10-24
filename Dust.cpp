#include "Dust.h"

Dust::Dust(Point center, Point velocity, double radius, Color color,double lifetime) {
    dustVelo = velocity;
    dustCenter = center;
    dustRad = radius;
    dustColor = color;
    lifeTime = lifetime;
}

void Dust::update(double tick) {
    dustCenter = dustCenter + dustVelo * tick;
    lifeTime-=tick;
}

bool Dust::isDead() const {
    return lifeTime<= 0.0;
}

void Dust::draw(Painter& painter) const {
    painter.draw(dustCenter, dustRad, dustColor);
}

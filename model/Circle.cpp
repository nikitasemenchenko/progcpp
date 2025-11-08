#include "Circle.h"
#include <iostream>

int Circle::nextId = 1;

Circle::Circle(double radius): id(nextId++), radius(radius) { }


int Circle::getId() const {
    return id;
}


std::string Circle::getType() const
{
    return "Circle";
}

void Circle::draw() const {
    std::cout<<"Circle #" << id <<" with radius " << radius << std::endl;
}
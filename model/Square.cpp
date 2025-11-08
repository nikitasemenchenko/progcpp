#include "Square.h"
#include <iostream>

int Square::nextId = 1;

Square::Square(double side) : id(nextId++), side(side) {}


int Square::getId() const {
    return id;
}


std::string Square::getType() const
{
    return "Square";
}

void Square::draw() const {
    std::cout<<"Square #" << id <<" with side " << side << std::endl;
}

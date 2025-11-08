#pragma once
#include "ShapeInterface.h"
#include <string>

class Circle: public ShapeInterface {
    private:
        int id;
        double radius;
        static int nextId;

    public:
        Circle(double radius);
        int getId() const override;
        std::string getType() const override;
        void draw() const override;
};
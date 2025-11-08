#pragma once
#include "ShapeInterface.h"
#include <string>

class Square: public ShapeInterface {
    private:
        int id;
        double side;
        static int nextId;

    public:
        Square(double side);
        int getId() const override;
        std::string getType() const override;
        void draw() const override;
};
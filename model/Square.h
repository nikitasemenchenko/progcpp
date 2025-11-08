#pragma once
#include "FigureInterface.h"
#include <string>

class Square: public FigureInterface {
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
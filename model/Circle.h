#pragma once
#include "FigureInterface.h"
#include <string>

class Circle: public FigureInterface {
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
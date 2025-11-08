#pragma once
#include <string>


//интерфейс графических объектов
//отвечает только за свои данные и отображение
class ShapeInterface {
    public:
        virtual ~ShapeInterface() = default;
        virtual int getId() const = 0;
        virtual std::string getType() const = 0;
        virtual void draw() const = 0;
};
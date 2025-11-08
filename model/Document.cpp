#include "Document.h"
#include "ShapeInterface.h"
#include <iostream>

int Document::nextId = 1;

Document::Document(): id(nextId++){}

int Document::getId() const {
    return id;
}

void Document::addShape(std::unique_ptr<ShapeInterface> shape) {
    shapes.push_back(std::move(shape));
}

void Document::deleteShape(int shapeId){
    for(int i = 0; i < shapes.size(); ++i){
        if(shapes[i]->getId() == shapeId){
            shapes.erase(shapes.begin() +i);
            break;
        }
    }
}

const std::vector<std::unique_ptr<ShapeInterface>>& Document::getShapes() const {
    return shapes;
}

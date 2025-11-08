#include "View.h"
#include <iostream>

void View::render(const DocumentInterface &document) const {
    std::cout << "printing document #" << document.getId() << std::endl;
    for(auto &shape: document.getShapes()){
        shape->draw();
    }
}
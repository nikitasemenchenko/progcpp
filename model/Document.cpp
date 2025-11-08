#include "Document.h"
#include "FigureInterface.h"
#include <iostream>

int Document::nextId = 1;

Document::Document(): id(nextId++){}

int Document::getId() const {
    return id;
}

void Document::addFigure(std::unique_ptr<FigureInterface> Figure) {
    Figures.push_back(std::move(Figure));
}

void Document::deleteFigure(int FigureId){
    for(int i = 0; i < Figures.size(); ++i){
        if(Figures[i]->getId() == FigureId){
            Figures.erase(Figures.begin() +i);
            break;
        }
    }
}

const std::vector<std::unique_ptr<FigureInterface>>& Document::getFigures() const {
    return Figures;
}

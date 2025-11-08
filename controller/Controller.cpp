#include "Controller.h"
#include "model/Document.h"
#include <iostream>

int  Controller::nextDocId = 1;

Controller::Controller(std::shared_ptr<ViewInterface> view): view(view) {}

std::shared_ptr<DocumentInterface> Controller::createNewDocument()
{
    auto doc = std::make_shared<Document>();
    documents.push_back(doc);
    std::cout<< "Created new document #" << doc->getId()<<std::endl;
    return doc;
}

std::shared_ptr<DocumentInterface> Controller::importDocument(const std::string &filename){
    auto doc = std::make_shared<Document>();
    //читаем файл
    documents.push_back(doc);
    std::cout<< "Imported document #" << doc->getId()<<" from file "<< filename << std::endl;
    return doc;
}

void Controller::exportDocument(const std::shared_ptr<DocumentInterface> &document, const std::string &filename){
    //записываем и сохраняем
    std::cout<< "Exported document #" << document->getId()<<" in file "<< filename << std::endl;
}

void Controller::addFigureToDocument(std::shared_ptr<DocumentInterface> &document, std::unique_ptr<FigureInterface> Figure){
    int FigureId = Figure->getId();
    std::string FigureType = Figure->getType();
    document->addFigure(std::move(Figure));
    std::cout << "Added figure " << FigureType << " #" << FigureId << " in the document #" << document->getId() << std::endl;
}

void Controller::removeFigureFromDocument(std::shared_ptr<DocumentInterface> &document, int FigureId){
    document->deleteFigure(FigureId);
    std::cout << "Deleted figure #" << FigureId << " from the document #" << document->getId() << std::endl;
}
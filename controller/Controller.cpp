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

void Controller::addShapeToDocument(std::shared_ptr<DocumentInterface> &document, std::unique_ptr<ShapeInterface> shape){
    int shapeId = shape->getId();
    std::string shapeType = shape->getType();
    document->addShape(std::move(shape));
    std::cout << "Added figure " << shapeType << " #" << shapeId << " in the document #" << document->getId() << std::endl;
}

void Controller::removeShapeFromDocument(std::shared_ptr<DocumentInterface> &document, int shapeId){
    document->deleteShape(shapeId);
    std::cout << "Deleted figure #" << shapeId << " from the document #" << document->getId() << std::endl;
}
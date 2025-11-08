#pragma once
#include "model/DocumentInterface.h"
#include "model/ShapeInterface.h"
#include "view/ViewInterface.h"

class ControllerInterface {
    public:
        virtual ~ControllerInterface() = default;
        virtual std::shared_ptr<DocumentInterface> createNewDocument() = 0;
        virtual std::shared_ptr<DocumentInterface> importDocument(const std::string& filename) = 0;
        virtual void exportDocument(const std::shared_ptr<DocumentInterface>& document, const std::string& filename) = 0;
        virtual void addShapeToDocument(std::shared_ptr<DocumentInterface>& document, std::unique_ptr<ShapeInterface> shape) = 0;
        virtual void removeShapeFromDocument(std::shared_ptr<DocumentInterface>& document, int shapeId) = 0;
};
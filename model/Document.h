#pragma once
#include "DocumentInterface.h"
#include <vector>
#include <memory>
#include "ShapeInterface.h"


class Document: public DocumentInterface {
    private:
        int id;
        std::vector<std::unique_ptr<ShapeInterface>> shapes;

        static int nextId;

    public:
        Document();
        int getId() const override; 
        void addShape(std::unique_ptr<ShapeInterface> shape) override;
        void deleteShape(int shapeId) override;
        const std::vector<std::unique_ptr<ShapeInterface>>& getShapes() const override;
};
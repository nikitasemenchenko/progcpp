#pragma once
#include "ShapeInterface.h"
#include <memory>
#include <vector>

//интерфейс документа который содержит графические объекты
//отвечает только за хранение и управление фигурами, не знает как они отображаются
class DocumentInterface {
    public:
        virtual ~DocumentInterface() = default;
        virtual int getId() const = 0;
        virtual void addShape(std::unique_ptr<ShapeInterface> shape) = 0;
        virtual void deleteShape(int shapeId) = 0;
        virtual const std::vector<std::unique_ptr<ShapeInterface>>& getShapes() const = 0;
};
#pragma once
#include "FigureInterface.h"
#include <memory>
#include <vector>

//интерфейс документа который содержит графические объекты
//отвечает только за хранение и управление фигурами, не знает как они отображаются
class DocumentInterface {
    public:
        virtual ~DocumentInterface() = default;
        virtual int getId() const = 0;
        virtual void addFigure(std::unique_ptr<FigureInterface> Figure) = 0;
        virtual void deleteFigure(int FigureId) = 0;
        virtual const std::vector<std::unique_ptr<FigureInterface>>& getFigures() const = 0;
};
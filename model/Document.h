#pragma once
#include "DocumentInterface.h"
#include <vector>
#include <memory>
#include "FigureInterface.h"


class Document: public DocumentInterface {
    private:
        int id;
        std::vector<std::unique_ptr<FigureInterface>> Figures;

        static int nextId;

    public:
        Document();
        int getId() const override; 
        void addFigure(std::unique_ptr<FigureInterface> Figure) override;
        void deleteFigure(int FigureId) override;
        const std::vector<std::unique_ptr<FigureInterface>>& getFigures() const override;
};
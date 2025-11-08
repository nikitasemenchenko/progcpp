#pragma once
#include "ControllerInterface.h"
#include <vector>
#include <memory>

class Controller: public ControllerInterface {
    private:
        std::vector<std::shared_ptr<DocumentInterface>> documents;
        std::shared_ptr<ViewInterface> view;
        static int nextDocId;
    
    public:
        Controller(std::shared_ptr<ViewInterface> view);
        std::shared_ptr<DocumentInterface> createNewDocument() override;
        std::shared_ptr<DocumentInterface> importDocument(const std::string& filename) override;
        void exportDocument(const std::shared_ptr<DocumentInterface>& document, const std::string& filename) override;
        void addFigureToDocument(std::shared_ptr<DocumentInterface>& document, std::unique_ptr<FigureInterface> Figure) override;
        void removeFigureFromDocument(std::shared_ptr<DocumentInterface>& document, int FigureId) override;
};
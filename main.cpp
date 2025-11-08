#include <iostream>
#include <memory>
#include "controller/Controller.h"
#include "view/View.h"
#include "model/Circle.h"
#include "model/Square.h"

int main(){
    auto view = std::make_shared<View>();
    auto controller = std::make_unique<Controller>(view);
    
    auto doc = controller->createNewDocument();
    auto circle = std::make_unique<Circle>(5.0);
    auto square = std::make_unique<Square>(10.0);
    controller->addShapeToDocument(doc, std::move(circle));
    controller->addShapeToDocument(doc, std::move(square));

    view->render(*doc);

    controller->removeShapeFromDocument(doc, 1);
    view->render(*doc);

    controller->exportDocument(doc, "document.graphic");

    auto importDoc = controller->importDocument("oldDocument.graphic");
    view->render(*importDoc);

    return 0;
}

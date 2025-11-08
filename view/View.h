#pragma once
#include "ViewInterface.h"

class View: public ViewInterface {
    public:
        void render(const DocumentInterface& document) const override;
};
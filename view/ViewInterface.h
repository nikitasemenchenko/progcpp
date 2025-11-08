#pragma once
#include <string>
#include "model/DocumentInterface.h"


class ViewInterface {
    public:
        virtual ~ViewInterface() = default;
        virtual void render(const DocumentInterface& document) const = 0;
};
#pragma once
#include "Options.h"

class Parser {
public:
    Options parse(int argc, char** argv);
};
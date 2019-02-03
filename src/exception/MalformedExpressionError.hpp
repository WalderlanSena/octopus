#ifndef _MALFORMED_EXPRESSION_ERROR_
#define _MALFORMED_EXPRESSION_ERROR_

#include <iostream>
#include "../include/termcolor/termcolor.hpp"

class MalformedExpressionError
{
public:
    void execute(std::string fileName, int line);
};

#endif
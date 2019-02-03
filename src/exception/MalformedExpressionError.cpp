#include "MalformedExpressionError.hpp"

void MalformedExpressionError::execute(std::string fileName, int line)
{
    std::cerr << termcolor::bold << "octopus:" << termcolor::red
			  << " Malformed expression near: " 
			  << termcolor::reset 
			  << line
              << " on file: " 
              << fileName 
              << std::endl;
    exit(1);
}
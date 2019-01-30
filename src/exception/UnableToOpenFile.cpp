/**
 * Octopus Compiler and toolkit
 * Copyright (C) 2018-2019 Octopus and CONTRIBUTORS
 *
 * This file is part of Octopus.
 *
 * Octopus is free software: you can redistribute it and/or modify
 * it under the terms of the MIT
 *
 * @author: Walderlan Sena <senawalderlan@gmail.com>
 * @license: https://github.com/WalderlanSena/octopus/blob/master/LICENSE
 * @version: v0.0.1
 */
#include "UnableToOpenFile.hpp"

void UnableToOpenFile::verify(std::string fileName)
{
	std::cerr << 
		termcolor::bold << "octopus: " << 
		termcolor::red <<  "[ERROR]" << termcolor::reset 
		<< " Unable to open file [ " << termcolor::blue 
		<< fileName << termcolor::reset << " ]" 
	<< std::endl;
	exit(1);
}
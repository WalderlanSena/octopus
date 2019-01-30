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
#ifndef _UNABLE_TO_OPEN_FILE_
#define _UNABLE_TO_OPEN_FILE_ 

#include <iostream>
#include "../include/termcolor/termcolor.hpp"

class UnableToOpenFile
{
public:
	static void verify(std::string fileName);
};

#endif
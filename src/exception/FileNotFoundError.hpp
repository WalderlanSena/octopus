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
#ifndef _FILE_NOT_FOUND_ERROR_
#define _FILE_NOT_FOUND_ERROR_

#include <iostream>
#include "../include/termcolor/termcolor.hpp"

class FileNotFoundError
{
public:
	static void execute(char *file);
};

#endif
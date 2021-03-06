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
#ifndef _LEXER_
#define _LEXER_

#include <string>
#include <vector>
#include "../token/Token.hpp"

class Lexer 
{	
public:
	
	std::vector<Token>tokens;

	std::string tok;
	
	bool _Lexer_checkKeyword(std::string tok);
};

#endif
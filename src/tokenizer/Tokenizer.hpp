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
#ifndef _TOKENIZER_
#define _TOKENIZER_

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <cstring>
#include "../token/Token.hpp"
#include "../lexer/Lexer.hpp"

class Tokenizer : public Lexer
{
public:

	Tokenizer(char *fileName);
	
	void _Tokenizer_build();

	void _Tokenizer_buildTokens(char currentChar);
	
	char _Tokenizer_getChar();

	char _Tokenizer_nextChar();

	void _Tokenizer_symbolCheck(char currentChar);	

	// bool _Tokenizer_checkKeyword(std::string tok);

	void printTokenList();

private:

	Token token;

	std::string fileName;
	
	std::fstream file;

};

#endif
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
#include "Token.hpp"

// Token::Token(std::string value, std::string type) {
//   	this->value = value;
//   	this->type  = type;
// }

std::string Token::_Token_getValue()
{
	return this->value;
}
	
void Token::_Token_setValue(std::string value)
{
	this->value = value;
}

std::string Token::_Token_getType()
{
	return this->type;
}

void Token::_Token_setType(std::string type)
{
	this->type = type;
}

int Token::_Token_getLine()
{
	return this->line;
}

void Token::_Token_setLine(int line)
{
	this->line = line;
}

void Token::_Token_setColumn(int column)
{
	this->column = column;
}

int Token::_Token_getColumn()
{
	return this->column;
}
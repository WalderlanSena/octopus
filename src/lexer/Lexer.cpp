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
#include "Lexer.hpp"

bool Lexer::_Lexer_checkKeyword(std::string tok)
{
	Token token;

	for (int i = 0; i < KEYWORD_VALUE; i++) {
		if (tok.compare(token.keywords[i]) == 0) {
			token._Token_setType(token.keywords[i]);
			token._Token_setValue(tok);
			this->tokens.push_back(token);
			this->tok = "";
			return true;
		}
	}
	return false;
}
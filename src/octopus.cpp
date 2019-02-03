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
#include "tokenizer/Tokenizer.hpp"
#include "parser/Parse.hpp"

int main(int argc, char *argv[])
{
	Tokenizer program(argv[1]);
	Parse stmt;

	program._Tokenizer_build();
	program.printTokenList();
	stmt.match(program);

	return 0;
}

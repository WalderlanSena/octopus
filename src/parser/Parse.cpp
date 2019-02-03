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
#include "Parse.hpp"

void Parse::match(Tokenizer &program)
{
    for (int i = 0; i < program.tokens.size(); i++) {
        if (program.tokens[i]._Token_getType() == "print") {
            OutputStatement outputStmt(program);
        } 
    }
}
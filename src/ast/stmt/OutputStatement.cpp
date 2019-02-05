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
#include "OutputStatement.hpp"

OutputStatement::OutputStatement(Tokenizer &tokenizer)
{
    std::string outputData = "";

    for (int i = 0; i < tokenizer.tokens.size(); i++) {
        if (tokenizer.tokens[i]._Token_getValue() != "\"" 
            && tokenizer.tokens[i]._Token_getValue() != "print" && tokenizer.tokens[i]._Token_getValue() != "-1") {
            outputData += tokenizer.tokens[i]._Token_getValue();
        }
        continue;
    }

    std::cout << outputData << std::endl;
}

void execute()
{
    
}
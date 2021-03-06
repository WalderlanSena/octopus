# Octopus Compiler and toolkit
# Copyright (C) 2018-2019 Octopus and CONTRIBUTORS
#
# This file is part of Octopus.
#
# Octopus is free software: you can redistribute it and/or modify
# it under the terms of the MIT
#
# @author: Walderlan Sena <senawalderlan@gmail.com>
# @license: https://github.com/WalderlanSena/octopus/blob/master/LICENSE
# @version: v0.0.1
CC=g++
STD=-std=c++11
EXAMPLE=examples/helloworld.oc
BIN=octopus
SYSTEM_PATH=/usr/local/bin
DEPENDENCIES=src/octopus.cpp src/tokenizer/* src/lexer/* src/parser/* src/token/* src/ast/stmt/* src/exception/*

main:
	$(CC) $(STD) $(DEPENDENCIES) -o $(BIN)

execute:
	./$(BIN) $(EXAMPLE) 

install:
	cp $(BIN) $(SYSTEM_PATH)

clean:
	rm -f $(BIN)

# Makefile config
CC=g++
STD=-std=c++11
EXAMPLE=helloWorld.oc
BIN=octopus
SYSTEM_PATH=/usr/local/bin
DEPENDENCIES=src/octopus.cpp src/tokenizer/* src/lexer/* src/parser/* src/token/* src/exception/*

main:
	$(CC) $(STD) $(DEPENDENCIES) -o $(BIN)

execute:
	./$(BIN) $(EXAMPLE) 

install:
	cp $(BIN) $(SYSTEM_PATH)

clean:
	rm -f $(BIN)

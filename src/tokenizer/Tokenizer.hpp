#ifndef _TOKENIZER_
#define _TOKENIZER_

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <cstring>
#include "../token/Token.hpp"

class Tokenizer
{
public:

	Tokenizer(char *fileName);
	
	void _Tokenizer_build();

	void _Tokenizer_buildTokens(char currentChar);
	
	char _Tokenizer_getChar();

	char _Tokenizer_nextChar();

	void _Tokenizer_symbolCheck(char currentChar);	

	bool _Tokenizer_checkKeyword(std::string tok);

	void printTokenList();

private:

	Token token;

	std::string fileName;
	
	std::fstream file;

	std::string tok;
	
	std::map <std::string, std::string> tokenTable;

	std::vector<Token>tokens;
};

#endif
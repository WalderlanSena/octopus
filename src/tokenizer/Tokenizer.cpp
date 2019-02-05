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
#include "Tokenizer.hpp"
#include "../exception/FileNotFoundError.hpp"
#include "../exception/UnableToOpenFile.hpp"

Tokenizer::Tokenizer(char *fileName)
{
	if (fileName == NULL) {
		FileNotFoundError::execute(fileName);
	}
	this->fileName = fileName;
}

void Tokenizer::_Tokenizer_build()
{
	char currentChar;
	int line   = 1;
	int column = 0;

	this->file.open(this->fileName, std::fstream::in);
	
	if (!this->file.is_open()) {
		UnableToOpenFile::verify(this->fileName);
	}

	while (!this->file.eof() && (int)(currentChar) != -1) {
		
		currentChar = this->file.get();
		
		column++;
		this->token._Token_setColumn(column);

		if ((int) currentChar == -1) {
			this->token._Token_setValue("-1");
			this->token._Token_setType("EOL");
			tokens.push_back(this->token);
		}

		if (currentChar == '\n') {
			line++;	
			this->token._Token_setLine(line);
		}
		
		if ((int) currentChar != -1 && currentChar != '\n' && currentChar != '\r' && currentChar != '\t') {
			this->_Tokenizer_buildTokens(currentChar);
		}
	}
	this->file.close();
}

void Tokenizer::_Tokenizer_buildTokens(char currentChar)
{
	int nc = (int) this->_Tokenizer_nextChar();
	int ic = (int) currentChar;

	if ((( ic >= 32 )  && ( ic <= 47 )) || ((ic >= 58)    && ( ic <= 64)) ||
		(( ic >= 91 )  && ( ic <= 94 )) || (( ic >= 123 ) && ( ic <= 126))) {
		this->tok += currentChar;
		this->_Tokenizer_symbolCheck(currentChar);
		this->tok = "";
	} else if ((( nc >= 97) && (nc <= 122) ) || ((nc >= 65) && (nc <= 90)) || 
			    ((nc >= 48) && (nc <= 57) )  ||(ic == 95 )){
		this->tok += currentChar;
	} else {
		this->tok += currentChar;
		if (isdigit(this->tok[0])) {
			this->token._Token_setType("INTEGER");
			this->token._Token_setValue(this->tok);
			Lexer::tokens.push_back(this->token);
		} else {
			if (!this->_Lexer_checkKeyword(this->tok)) {
				this->token._Token_setType("IDENT");
				this->token._Token_setValue(this->tok);
				Lexer::tokens.push_back(this->token);
			}
		}
		this->tok = "";
	}
}

char Tokenizer::_Tokenizer_getChar()
{
	char myChar = this->file.get();
	if ( (int)(myChar) != -1 ) {
		return myChar;
	}
	return ' ';
}
	
char Tokenizer::_Tokenizer_nextChar()
{
	char myChar = this->file.get();
	this->file.unget();
	if ((int)(myChar) != -1){
		return myChar;
	}
	return ' ';
}

/**
 * O método symbolCheck é chamado quando um token potencial não começa com um caractere alfanumérico
 */
void Tokenizer::_Tokenizer_symbolCheck(char currentChar)
{	
	bool flag = false;

	switch (currentChar) {
		case ':':
			if (this->_Tokenizer_nextChar() == ':' ){
				this->token._Token_setType("SCOPE_RESOLUTION");
				this->token._Token_setValue(this->tok + this->_Tokenizer_getChar());
				break;
			}
			this->token._Token_setType("COLON");
			this->token._Token_setValue(this->tok);
			break;
		case '+':
			if (this->_Tokenizer_nextChar() == '+' ){
				this->token._Token_setType("INCREMENT");
				this->token._Token_setValue(this->tok + this->_Tokenizer_getChar());
				break;
			}
			if (this->_Tokenizer_nextChar() == '=' ) {
				this->token._Token_setType("ASSIGN_SUM");
				this->token._Token_setValue(this->tok + this->_Tokenizer_getChar());
				break;
			}
			this->token._Token_setType("ADD");
			this->token._Token_setValue(this->tok);
			break;
		case '-':
			if (this->_Tokenizer_nextChar() == '-' ) {
				this->token._Token_setType("DECREMENT");
				this->token._Token_setValue(this->tok + this->_Tokenizer_getChar());
				break;
			} 
			if (this->_Tokenizer_nextChar() == '=' ) {
				this->token._Token_setType("ASSIGN_DIFF");
				this->token._Token_setValue(this->tok + this->_Tokenizer_getChar());
				break;
			}
			if (this->_Tokenizer_nextChar() == '>' ) {
				this->token._Token_setType("ELEMPOINTER");
				this->token._Token_setValue(this->tok + this->_Tokenizer_getChar());
				break;
			}
			if (this->_Tokenizer_nextChar() == '*' ) {
				this->token._Token_setType("POINTERTOMEMB");
				this->token._Token_setValue(this->tok + this->_Tokenizer_getChar());
				break;
			}
			this->token._Token_setType("SUBTRACT");
			this->token._Token_setValue(this->tok);
			break;
		case '(':
			this->token._Token_setType("LPAREN");
			this->token._Token_setValue(this->tok);
			break;
		case ')':
			this->token._Token_setType("RPAREN");
			this->token._Token_setValue(this->tok);
			break;
		case '[':
			this->token._Token_setType("LBPAREN");
			this->token._Token_setValue(this->tok);
			break;
		case ']':
			this->token._Token_setType("RBPAREN");
			this->token._Token_setValue(this->tok);
			break;
		case '{':
			this->token._Token_setType("LSPAREN");
			this->token._Token_setValue(this->tok);
			break;
		case '}':
			this->token._Token_setType("RSPAREN");
			this->token._Token_setValue(this->tok);
			break;
		case '.':
			if (this->_Tokenizer_nextChar() == '*' ) {
				this->token._Token_setType("POINTERTOMEMBER");
				this->token._Token_setValue(this->tok + this->_Tokenizer_getChar());
				break;
			}
			this->token._Token_setType("ELEMREF");
			this->token._Token_setValue(this->tok);
			break;
		case '!':
			if (this->_Tokenizer_nextChar() == '=' ){
				this->token._Token_setType("NOT_EQ");
				this->token._Token_setValue(this->tok + this->_Tokenizer_getChar());
				break;
			}
			this->token._Token_setType("NOT");
			this->token._Token_setValue(this->tok);
			break;
		case '~':
			this->token._Token_setType("BITWISE_NOT");
			this->token._Token_setValue(this->tok);
			break;
		case '*':
			if (this->_Tokenizer_nextChar() == '=' ){
				this->token._Token_setType("ASSIGN_PROD");
				this->token._Token_setValue(this->tok + this->_Tokenizer_getChar());
			break;
			}
			this->token._Token_setType("MULT");
			this->token._Token_setValue(this->tok);
			break;
		case '&':
			if (this->_Tokenizer_nextChar() == '&') {
				this->token._Token_setType("LOGICAL_AND");
				this->token._Token_setValue(tok + this->_Tokenizer_getChar());
				break;
			}
			if (this->_Tokenizer_nextChar() == '=') {
				this->token._Token_setType("BITWISE_AND_ASSIGN");
				this->token._Token_setValue(this->tok + this->_Tokenizer_getChar());
				break;
			}
			this->token._Token_setType("BITWISE_AND");
			this->token._Token_setValue(this->tok);
			break;
		case '/':
			if (this->_Tokenizer_nextChar() == '=' ) {
				this->token._Token_setType("ASSIGN_QUOTIENT");
				this->token._Token_setValue(this->tok + this->_Tokenizer_getChar());
				break;
			} 
			
			if (this->_Tokenizer_nextChar() == '*' ) {
				
				bool invar = true;

				while (invar) {
					if (this->_Tokenizer_nextChar() == '*' ) {
						this->_Tokenizer_getChar();
						if (this->_Tokenizer_nextChar() == '/' ) {
							this->_Tokenizer_getChar();
							invar = false;
							flag = true;
						}
					} else {
						this->_Tokenizer_getChar();
					}
				}
			}
			if (this->_Tokenizer_nextChar() == '/' ){

				while(this->_Tokenizer_nextChar() != '\n' && this->_Tokenizer_nextChar() != '\r' ){
					this->_Tokenizer_getChar();
				}
				flag = true;
			}
			
			this->token._Token_setType("DIVISION");
			this->token._Token_setValue(this->tok);
			break;
		case '\\':
			if (this->_Tokenizer_nextChar() == 'n' ){
				this->token._Token_setType("NEW_LINE");
				this->token._Token_setValue(this->tok + this->_Tokenizer_getChar());
				break;
			}
			if (this->_Tokenizer_nextChar() == 't' ) {
				this->token._Token_setType("HORZ_TAB");
				this->token._Token_setValue(this->tok + this->_Tokenizer_getChar());
				break;
			}
			if (this->_Tokenizer_nextChar() == 'r' ){
				this->token._Token_setType("CARRIAGE_RETURN");
				this->token._Token_setValue(this->tok + this->_Tokenizer_getChar());
				break;
			}
			break;
		case '%':
			if (this->_Tokenizer_nextChar() == '=' ){
				this->token._Token_setType("ASSIGN_REMAINDER");
				this->token._Token_setValue(this->tok + this->_Tokenizer_getChar());
				break;
			}
			this->token._Token_setType("REMAINDER");
			this->token._Token_setValue(this->tok);
			break;
		case '<':
			if (this->_Tokenizer_nextChar() == '<' ){
				this->token._Token_setType("LSHIFT");
				this->token._Token_setValue(this->tok + this->_Tokenizer_getChar());
				if (this->_Tokenizer_nextChar() == '=' ){
					this->token._Token_setType("LSHIFT_ASSIGN");
					this->token._Token_setValue(this->tok + this->_Tokenizer_getChar());
				}
				break;
			}
			if (this->_Tokenizer_nextChar() == '=' ){
				this->token._Token_setType("LESS_EQ");
				this->token._Token_setValue(this->tok + this->_Tokenizer_getChar());
				break;
			}
			
			this->token._Token_setType("LESS");
			this->token._Token_setValue(this->tok);
			break;
		case '>':
			if (this->_Tokenizer_nextChar() == '>' ){
				this->token._Token_setType("RSHIFT");
				this->token._Token_setValue(this->tok + this->_Tokenizer_getChar());

				if (this->_Tokenizer_nextChar() == '=' ){
					this->token._Token_setType("RSHIFT_ASSIGN");
					this->token._Token_setValue(this->tok + this->_Tokenizer_getChar());
				}
				break;
			}
			if (this->_Tokenizer_nextChar() == '=' ){
				this->token._Token_setType("GREATER_EQ");
				this->token._Token_setValue(this->tok + this->_Tokenizer_getChar());
				break;
			}
			this->token._Token_setType("GREATER");
			this->token._Token_setValue(this->tok);
			break;
		case '=':
			if (this->_Tokenizer_nextChar() == '=' ){
				this->token._Token_setType("EQUIVALENCE");
				this->token._Token_setValue(this->tok + this->_Tokenizer_getChar());
				break;
			}
			this->token._Token_setType("EQUAL");
			this->token._Token_setValue(this->tok);
			break;
		case '^':
			if (this->_Tokenizer_nextChar() == '=' ){
				this->token._Token_setType("BITWISE_XOR_ASSIGN");
				this->token._Token_setType(this->tok + this->_Tokenizer_getChar());
				break;
			}
			this->token._Token_setType("XOR");
			this->token._Token_setValue(this->tok);
			break;
		case '|':
			if (this->_Tokenizer_nextChar() == '|' ){
				this->token._Token_setType("LOGICAL_OR");
				this->token._Token_setValue(this->tok + this->_Tokenizer_getChar());
				break;
			}
			if (this->_Tokenizer_nextChar() == '=' ) {
				this->token._Token_setType("BITWISE_OR_ASSIGN");
				this->token._Token_setValue(this->tok + this->_Tokenizer_getChar());
				break;
			}	
			this->token._Token_setType("BITWISE_OR");
			this->token._Token_setValue(this->tok);
			break;
		case '?':
			if (this->_Tokenizer_nextChar() == ':' ){
				this->token._Token_setType("TERNARY_COND");
				this->token._Token_setValue(this->tok + this->_Tokenizer_getChar());
				break;
			}
			flag = true;
			break;
		case ',':
			this->token._Token_setType("COMMA");
			this->token._Token_setValue(this->tok);
			break;
		case ';':
			this->token._Token_setType("SEMICOLON");
			this->token._Token_setValue(this->tok);
			break;
		case '\"':
			this->token._Token_setType("DOUBLE_QUOTE");
			this->token._Token_setValue(this->tok);
			break;
		case '\'':
			this->token._Token_setType("SINGLE_QUOTE");
			this->token._Token_setValue(this->tok);
			break;
		default:
			flag = true;
		break;

	}

	if (!flag) {
    	tokens.push_back(this->token);
	}
}

void Tokenizer::printTokenList()
{
	// std::cout << "\nTokens:\n\n";
    
	// for( int i = 0; i < tokens.size(); i++) {
	// 	std::string num;
	// 	num = tokens[i]._Token_getValue();
	// 	std::cout << tokens[i]._Token_getType() << "\t\t\t->\t" << tokens[i]._Token_getValue() << std::endl;
	// }

}
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
#ifndef _TOKEN_
#define _TOKEN_

#include <string>

#define KEYWORD_VALUE 17

#define ENDMARKER	0
#define NAME        1
#define NUMBER      2
#define STRING      3
#define NEWLINE     4
#define INDENT		5

class Token
{
public:
	
	std::string value;
  	std::string type;
	std::string keywords[KEYWORD_VALUE]{
		"if",
		"endif",
		"and", 
		"or", 
		"not",
		"while",
		"do",
		"done", 
		"print",
		"input",
		"for",
		"endfor", 
		"int", 
		"string", 
		"double",  
		"func", 
		"ret"
	};

	std::string _Token_getValue();
	
	void _Token_setValue(std::string value);

	std::string _Token_getType();

	void _Token_setType(std::string value);

	int _Token_getLine();

	void _Token_setLine(int line);

private:
 	int line;
};

#endif
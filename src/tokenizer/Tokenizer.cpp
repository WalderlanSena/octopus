#include "Tokenizer.hpp"
#include "../exception/FileNotFoundError.hpp"
#include "../exception/UnableToOpenFile.hpp"

Tokenizer::Tokenizer(char *fileName)
{
	if (fileName == NULL) {
		FileNotFoundError::verify(fileName);
	}
	this->fileName = fileName;
}

void Tokenizer::_Tokenizer_build()
{
	char currentChar;
	
	this->file.open(this->fileName, std::fstream::in);
	
	if (!this->file.is_open()) {
		UnableToOpenFile::verify(this->fileName);
	}

	while (!this->file.eof() && (int)(currentChar) != -1) {
		
		currentChar = this->file.get();
		
		if ((int) currentChar == -1) {
			Token octok;
			octok._Token_setType("-1");
			octok._Token_setValue("EOL");
			tokens.push_back(octok);
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
	} else if ((( nc >= 97) && (nc <= 122) ) || ((nc >= 65) && (nc <= 90)) || ((nc >= 48) && (nc <= 57) ) ||
			(ic == 95 )){
		this->tok += currentChar;
	} else {
		this->tok += currentChar;
		if(isdigit(this->tok[0])){
			Token t;
			t._Token_setValue("INTEGER");
			t._Token_setType(this->tok);
			tokens.push_back(t);
		} else {
			if (!this->_Tokenizer_checkKeyword(this->tok)){
				Token t;
				t._Token_setValue("IDENT");
				t._Token_setType(this->tok);
				tokens.push_back(t);
				}
			}
			this->tok = "";
	}
}

char Tokenizer::_Tokenizer_getChar()
{
	char myChar = this->file.get();
	if( (int)(myChar) != -1 ){
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

bool Tokenizer::_Tokenizer_checkKeyword(std::string tok)
{
	Token octok;

	for (int i = 0; i < KEYWORD_VALUE; i++) {
		if (tok.compare(octok.keywords[i]) == 0) {
			octok._Token_setValue(octok.keywords[i]);
			octok._Token_setType(tok);
			tokens.push_back(octok);
			this->tok = "";
			return true;
		}
	}
	return false;
}

/**
 * O método symbolCheck é chamado quando um token potencial não começa com um caractere alfanumérico
 */
void Tokenizer::_Tokenizer_symbolCheck(char currentChar)
{
	Token tk;
	
	bool flag = false;

	switch (currentChar) {
	case ':':
		if (this->_Tokenizer_nextChar() == ':' ){
			tk._Token_setValue("SCOPE_RESOLUTION");
			tk._Token_setType(this->tok + this->_Tokenizer_getChar());
			break;
		}
		tk._Token_setValue("COLON");
		tk._Token_setType(this->tok);
		break;
	case '+':
		if (this->_Tokenizer_nextChar() == '+' ){
			tk._Token_setValue("INCREMENT");
			tk._Token_setType(this->tok + this->_Tokenizer_getChar());
			break;
		}
		if (this->_Tokenizer_nextChar() == '=' ) {
			tk._Token_setValue("ASSIGN_SUM");
			tk._Token_setType(this->tok + this->_Tokenizer_getChar());
			break;
		}
		tk._Token_setValue("ADD");
		tk._Token_setType(this->tok);
		break;
	case '-':
		if (this->_Tokenizer_nextChar() == '-' ) {
			tk._Token_setValue("DECREMENT");
			tk._Token_setType(this->tok + this->_Tokenizer_getChar());
			break;
		} 
		if (this->_Tokenizer_nextChar() == '=' ) {
			tk._Token_setValue("ASSIGN_DIFF");
			tk._Token_setType(this->tok + this->_Tokenizer_getChar());
			break;
		}
		if (this->_Tokenizer_nextChar() == '>' ) {
			tk._Token_setValue("ELEMPOINTER");
			tk._Token_setType(this->tok + this->_Tokenizer_getChar());
			break;
		}
		if (this->_Tokenizer_nextChar() == '*' ) {
			tk._Token_setValue("POINTERTOMEMB");
			tk._Token_setType(this->tok + this->_Tokenizer_getChar());
			break;
		}
		tk._Token_setValue("SUBTRACT");
		tk._Token_setType(this->tok);
		break;
	case '(':
		tk._Token_setValue("LPAREN");
		tk._Token_setType(this->tok);
		break;
	case ')':
		tk._Token_setValue("RPAREN");
		tk._Token_setType(this->tok);
		break;
	case '[':
		tk._Token_setValue("LBPAREN");
		tk._Token_setType(this->tok);
		break;
	case ']':
		tk._Token_setValue("RBPAREN");
		tk._Token_setType(this->tok);
		break;
	case '{':
		tk._Token_setValue("LSPAREN");
		tk._Token_setType(this->tok);
		break;
	case '}':
		tk._Token_setValue("RSPAREN");
		tk._Token_setType(this->tok);
		break;
	case '.':
		if (this->_Tokenizer_nextChar() == '*' ) {
			tk._Token_setValue("POINTERTOMEMBER");
			tk._Token_setType(this->tok + this->_Tokenizer_getChar());
			break;
		}
		tk._Token_setValue("ELEMREF");
		tk._Token_setType(this->tok);
		break;
	case '!':
		if (this->_Tokenizer_nextChar() == '=' ){
			tk._Token_setValue("NOT_EQ");
			tk._Token_setType(this->tok + this->_Tokenizer_getChar());
			break;
		}
		tk._Token_setValue("NOT");
		tk._Token_setType(this->tok);
		break;
	case '~':
		tk._Token_setValue("BITWISE_NOT");
		tk._Token_setType(this->tok);
		break;
	case '*':
		if (this->_Tokenizer_nextChar() == '=' ){
			tk._Token_setValue("ASSIGN_PROD");
			tk._Token_setType(this->tok + this->_Tokenizer_getChar());
		break;
		}
		tk._Token_setValue("MULT");
		tk._Token_setType(this->tok);
		break;
	case '&':
		if (this->_Tokenizer_nextChar() == '&') {
			tk._Token_setValue("LOGICAL_AND");
			tk._Token_setType(tok + this->_Tokenizer_getChar());
			break;
		}
		if (this->_Tokenizer_nextChar() == '=') {
			tk._Token_setValue("BITWISE_AND_ASSIGN");
			tk._Token_setType(this->tok + this->_Tokenizer_getChar());
			break;
		}
		tk._Token_setValue("BITWISE_AND");
		tk._Token_setType(this->tok);
		break;
	case '/':
		if (this->_Tokenizer_nextChar() == '=' ) {
			tk._Token_setValue("ASSIGN_QUOTIENT");
			tk._Token_setType(this->tok + this->_Tokenizer_getChar());
			break;
		} 
		
		if (this->_Tokenizer_nextChar() == '*' ){
			
			bool invar = true;

			while (invar) {
				if (this->_Tokenizer_nextChar() == '*' ){
					this->_Tokenizer_getChar();
					if (this->_Tokenizer_nextChar() == '/' ){
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
		
		tk._Token_setValue("DIVISION");
		tk._Token_setType(this->tok);
		break;
	case '\\':
		if (this->_Tokenizer_nextChar() == 'n' ){
			tk._Token_setValue("NEW_LINE");
			tk._Token_setType(this->tok + this->_Tokenizer_getChar());
			break;
		}
		if (this->_Tokenizer_nextChar() == 't' ) {
			tk._Token_setValue("HORZ_TAB");
			tk._Token_setType(this->tok + this->_Tokenizer_getChar());
			break;
		}
		if (this->_Tokenizer_nextChar() == 'r' ){
			tk._Token_setValue("CARRIAGE_RETURN");
			tk._Token_setType(this->tok + this->_Tokenizer_getChar());
			break;
		}
		break;
	case '%':
		if (this->_Tokenizer_nextChar() == '=' ){
			tk._Token_setValue("ASSIGN_REMAINDER");
			tk._Token_setType(this->tok + this->_Tokenizer_getChar());
			break;
		}
		tk._Token_setValue("REMAINDER");
		tk._Token_setType(this->tok);
		break;
	case '<':
		if (this->_Tokenizer_nextChar() == '<' ){
			tk._Token_setValue("LSHIFT");
			tk._Token_setType(this->tok + this->_Tokenizer_getChar());
			if (this->_Tokenizer_nextChar() == '=' ){
				tk._Token_setValue("LSHIFT_ASSIGN");
				tk._Token_setType(this->tok + this->_Tokenizer_getChar());
			}
			break;
		}
		if (this->_Tokenizer_nextChar() == '=' ){
			tk._Token_setValue("LESS_EQ");
			tk._Token_setType(this->tok + this->_Tokenizer_getChar());
			break;
		}
		
		tk._Token_setValue("LESS");
		tk._Token_setType(this->tok);
		break;
	case '>':
		if (this->_Tokenizer_nextChar() == '>' ){
			tk._Token_setValue("RSHIFT");
			tk._Token_setType(this->tok + this->_Tokenizer_getChar());

			if (this->_Tokenizer_nextChar() == '=' ){
				tk._Token_setValue("RSHIFT_ASSIGN");
				tk._Token_setType(this->tok + this->_Tokenizer_getChar());
			}
			break;
		}
		if (this->_Tokenizer_nextChar() == '=' ){
			tk._Token_setValue("GREATER_EQ");
			tk._Token_setType(this->tok + this->_Tokenizer_getChar());
			break;
		}
		tk._Token_setValue("GREATER");
		tk._Token_setType(this->tok);
		break;
	case '=':
		if (this->_Tokenizer_nextChar() == '=' ){
			tk._Token_setValue("EQUIVALENCE");
			tk._Token_setType(this->tok + this->_Tokenizer_getChar());
			break;
		}
		tk._Token_setValue("EQUAL");
		tk._Token_setType(this->tok);
		break;
	case '^':
		if (this->_Tokenizer_nextChar() == '=' ){
			tk._Token_setValue("BITWISE_XOR_ASSIGN");
			tk._Token_setValue(this->tok + this->_Tokenizer_getChar());
			break;
		}
		tk._Token_setValue("XOR");
		tk._Token_setType(this->tok);
		break;
	case '|':
		if (this->_Tokenizer_nextChar() == '|' ){
			tk._Token_setValue("LOGICAL_OR");
			tk._Token_setType(this->tok + this->_Tokenizer_getChar());
			break;
		}
		if (this->_Tokenizer_nextChar() == '=' ) {
			tk._Token_setValue("BITWISE_OR_ASSIGN");
			tk._Token_setType(this->tok + this->_Tokenizer_getChar());
			break;
		}	
		tk._Token_setValue("BITWISE_OR");
		tk._Token_setType(this->tok);
		break;
	case '?':
		if (this->_Tokenizer_nextChar() == ':' ){
			tk._Token_setValue("TERNARY_COND");
			tk._Token_setType(this->tok + this->_Tokenizer_getChar());
			break;
		}
		flag = true;
		break;
	case ',':
		tk._Token_setValue("COMMA");
		tk._Token_setType(this->tok);
		break;
	case ';':
		tk._Token_setValue("SEMICOLON");
		tk._Token_setType(this->tok);
		break;
	case '\"':
		tk._Token_setValue("DOUBLE_QUOTE");
		tk._Token_setType(this->tok);
		break;
	case '\'':
		tk._Token_setValue("SINGLE_QUOTE");
		tk._Token_setType(this->tok);
		break;
	default:
		flag = true;
		break;

	}

	if (!flag) {
    	tokens.push_back(tk);
	}
}

void Tokenizer::printTokenList()
{
	
	std::cout << "\nTokens:\n\n";
    
	for( int i = 0; i < tokens.size(); i++) {
		std::string num;
		num = tokens[i]._Token_getValue();
		std::cout << tokens[i]._Token_getValue() << "\t\t\t->\t" << tokens[i]._Token_getType() << std::endl;
	}

}
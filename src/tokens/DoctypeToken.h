#ifndef DOCTYPE_TOKEN_H
#define DOCTYPE_TOKEN_H

#include "Token.h"

// <!doctype
class DoctypeToken : public Token
{
public:
	DoctypeToken(std::string value, TextPosition pos) : Token(value, pos) {}
	DoctypeToken(std::string value, int ln, int cn, int global) : Token(value, ln, cn, global) {}
	void print();

	TokenType getType();
};

#endif

#ifndef DOCTYPE_TOKEN_H
#define DOCTYPE_TOKEN_H

#include "Token.h"

// <!doctype
class DoctypeToken : public Token
{
public:
	const TokenType type = TokenType::Doctype;

	DoctypeToken(std::string value, int ln, int cn, int global) : Token(value, ln, cn, global) {}
	void print();
};

#endif

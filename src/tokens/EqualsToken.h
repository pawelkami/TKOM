#ifndef EQUALSTOKEN_H
#define EQUALSTOKEN_H

#include "Token.h"

// =
class EqualsToken : public Token
{
public:
	const TokenType type = TokenType::Equals;

	EqualsToken(std::string value, int ln, int cn, int global) : Token(value, ln, cn, global) {}

	void print();

};

#endif

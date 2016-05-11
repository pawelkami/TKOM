#ifndef EQUALSTOKEN_H
#define EQUALSTOKEN_H

#include "Token.h"

// =
class EqualsToken : public Token
{
public:
	const TokenType type = TokenType::Equals;

	EqualsToken(TextPosition pos) : Token("=", pos), type(Equals) {}

	EqualsToken(int ln, int cn, int global) : Token("=", ln, cn, global), type(Equals) {}

	void print();

	TokenType getType();


};

#endif

#ifndef EQUALSTOKEN_H
#define EQUALSTOKEN_H

#include "Token.h"

// =
class EqualsToken : public Token
{
public:
	const TokenType type = TokenType::Equals;

	EqualsToken(TextPosition pos) : Token("=", pos) {}

	EqualsToken(int ln, int cn, int global) : Token("=", ln, cn, global) {}

	void print();

};

#endif

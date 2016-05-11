#ifndef QUOTETOKEN_H
#define QUOTETOKEN_H

#include "Token.h"

class QuoteToken : public Token
{
public:
	QuoteToken(TextPosition pos) : Token("\"", pos) {}

	QuoteToken(int ln, int cn, int global) : Token("\"", ln, cn, global) {}

	void print();

	TokenType getType();

};

#endif

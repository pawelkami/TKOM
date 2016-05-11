#ifndef QUOTETOKEN_H
#define QUOTETOKEN_H

#include "Token.h"

class QuoteToken : public Token
{
public:
	const TokenType type = TokenType::Quote;

	QuoteToken(TextPosition pos) : Token("\"", pos) {}

	QuoteToken(int ln, int cn, int global) : Token("\"", ln, cn, global) {}

	void print();
};

#endif

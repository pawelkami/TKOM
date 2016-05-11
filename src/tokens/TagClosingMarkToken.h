#ifndef TAGCLOSINGMARKTOKEN_H
#define TAGCLOSINGMARKTOKEN_H

#include "Token.h"

// >
class TagClosingMarkToken : public Token
{
public:
	const TokenType type = TokenType::TagClosingMark;

	TagClosingMarkToken(TextPosition pos) : Token(">", pos) {}
	TagClosingMarkToken(int ln, int cn, int global) : Token(">", ln, cn, global) {}

	void print();
};

#endif

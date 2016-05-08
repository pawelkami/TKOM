#ifndef TAGCLOSINGMARKTOKEN_H
#define TAGCLOSINGMARKTOKEN_H

#include "Token.h"

// >
class TagClosingMarkToken : public Token
{
public:
	const TokenType type = TokenType::TagClosingMark;

	TagClosingMarkToken(std::string value, int ln, int cn, int global) : Token(value, ln, cn, global) {}

	void print();
};

#endif

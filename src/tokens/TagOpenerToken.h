#ifndef TAGOPENERTOKEN_H
#define TAGOPENERTOKEN_H

#include "Token.h"

// <tag
class TagOpenerToken : public Token
{
public:
	const TokenType type = TokenType::TagOpener;

	TagOpenerToken(std::string value, int ln, int cn, int global) : Token(value, ln, cn, global) {}

	void print();
};

#endif

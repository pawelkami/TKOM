#ifndef CLOSINGTAGTOKEN_H
#define CLOSINGTAGTOKEN_H

#include "Token.h"

// </tag
class ClosingTagToken : public Token
{
public:
	const TokenType type = TokenType::ClosingTag;

	ClosingTagToken(std::string value, int ln, int cn, int global) : Token(value, ln, cn, global) {}

	void print();
};

#endif
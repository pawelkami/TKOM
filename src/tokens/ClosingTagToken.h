#ifndef CLOSINGTAGTOKEN_H
#define CLOSINGTAGTOKEN_H

#include "Token.h"

// </
class ClosingTagToken : public Token
{
public:
	const TokenType type = TokenType::ClosingTag;

	ClosingTagToken(TextPosition textpos) : Token("</", textpos) {}
	ClosingTagToken(int ln, int cn, int global) : Token("</", ln, cn, global) {}

	void print();
};

#endif
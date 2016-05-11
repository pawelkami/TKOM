#ifndef CLOSINGTAGTOKEN_H
#define CLOSINGTAGTOKEN_H

#include "Token.h"

// </
class ClosingTagToken : public Token
{
public:
	ClosingTagToken(TextPosition textpos) : Token("</", textpos){}
	ClosingTagToken(int ln, int cn, int global) : Token("</", ln, cn, global) {}

	void print();

	TokenType getType();
};

#endif
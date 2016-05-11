#ifndef EMPTYCLOSINGTAGTOKEN_H
#define EMPTYCLOSINGTAGTOKEN_H

#include "Token.h"

// />
class EmptyClosingTagToken : public Token
{
public:
	const TokenType type = TokenType::EmptyClosingTag;

	EmptyClosingTagToken(TextPosition pos) : Token("/>", pos) {}

	EmptyClosingTagToken(int ln, int cn, int global) : Token("/>", ln, cn, global) {}

	void print();
};


#endif

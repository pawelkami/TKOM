#ifndef EMPTYCLOSINGTAGTOKEN_H
#define EMPTYCLOSINGTAGTOKEN_H

#include "Token.h"

// />
class EmptyClosingTagToken : public Token
{
public:

	EmptyClosingTagToken(TextPosition pos) : Token("/>", pos) {}

	EmptyClosingTagToken(int ln, int cn, int global) : Token("/>", ln, cn, global) {}

	void print();
	TokenType getType();

};


#endif

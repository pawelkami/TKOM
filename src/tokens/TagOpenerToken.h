#ifndef TAGOPENERTOKEN_H
#define TAGOPENERTOKEN_H

#include "Token.h"

// <
class TagOpenerToken : public Token
{
public:
	TagOpenerToken(TextPosition pos) : Token("<", pos) {}
	TagOpenerToken( int ln, int cn, int global) : Token("<", ln, cn, global) {}

	void print();

	TokenType getType();

};

#endif

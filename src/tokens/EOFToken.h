#ifndef EOFTOKEN_H
#define EOFTOKEN_H


#include "Token.h"
class EOFToken :
	public Token
{
public:
	const TokenType type = TokenType::None;

	EOFToken(TextPosition pos) : Token("", pos) {}

	EOFToken(int ln, int cn, int global) : Token("", ln, cn, global) {}

	void print() {}
};

#endif

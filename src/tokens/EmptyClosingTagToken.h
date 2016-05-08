#ifndef EMPTYCLOSINGTAGTOKEN_H
#define EMPTYCLOSINGTAGTOKEN_H

#include "Token.h"

// />
class EmptyClosingTagToken : public Token
{
public:
	const TokenType type = TokenType::EmptyClosingTag;

	EmptyClosingTagToken(std::string value, int ln, int cn, int global) : Token(value, ln, cn, global) {}

	void print();
};


#endif

#ifndef ATTRIBUTEKEYTOKEN_H
#define ATTRIBUTEKEYTOKEN_H

#include "Token.h"

// key
class AttributeKeyToken : public Token
{
public:
	const TokenType type = TokenType::AttributeKey;
	AttributeKeyToken(std::string value, int ln, int cn, int global) : Token(value, ln, cn, global) {}
	void print();
};

#endif

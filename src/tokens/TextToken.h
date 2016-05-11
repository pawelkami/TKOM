#ifndef TEXTTOKEN_H
#define TEXTTOKEN_H

#include "Token.h"

// plain text bêd¹cy pomiêdzy tagami
class TextToken : public Token
{
public:
	const TokenType type = TokenType::Text;

	void print();
	TextToken(std::string value, TextPosition pos) : Token(value, pos) {}

	TextToken(std::string value, int ln, int cn, int global) : Token(value, ln, cn, global) {}

};

#endif

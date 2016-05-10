#ifndef PLAINTEXTTOKEN_H
#define PLAINTEXTTOKEN_H

#include "Token.h"

// plain text b�d�cy pomi�dzy tagami
class PlainTextToken : public Token
{
public:
	const TokenType type = TokenType::PlainText;

	void print();
	PlainTextToken(std::string value, int ln, int cn, int global) : Token(value, ln, cn, global) {}

};

#endif

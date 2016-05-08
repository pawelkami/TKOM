#ifndef COMMENTTOKEN_H
#define COMMENTTOKEN_H

#include "Token.h"

class CommentToken : public Token
{
public:
	const TokenType type = TokenType::Comment;

	CommentToken(std::string value, int ln, int cn, int global) : Token(value, ln, cn, global) {}

	void print();
};

#endif
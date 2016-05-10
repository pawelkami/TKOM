#ifndef ATTRIBUTEVALUETOKEN_H
#define ATTRIBUTEVALUETOKEN_H

#include "Token.h"

// value
class AttributeValueToken : public Token
{
private:
	char quoteType;		// " lub '

public:
	const TokenType type = TokenType::AttributeValue;

	AttributeValueToken(std::string val, char quote);
	AttributeValueToken(std::string value, int ln, int cn, int global, char q) : Token(value, ln, cn, global), quoteType(q) {}

	char getQuoteType();
	void setQuoteType(char quote);
	void print();
};

#endif

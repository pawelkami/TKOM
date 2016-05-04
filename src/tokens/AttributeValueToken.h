#ifndef ATTRIBUTEVALUETOKEN_H
#define ATTRIBUTEVALUETOKEN_H

#include "Token.h"

class AttributeValueToken : public Token
{
private:
	char quoteType;		// " lub '

public:
	AttributeValueToken(std::string val, char quote);

	char getQuoteType();
	void setQuoteType(char quote);
	void print();
};

#endif

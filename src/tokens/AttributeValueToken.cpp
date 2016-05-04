#include "AttributeValueToken.h"
#include <iostream>

AttributeValueToken::AttributeValueToken(std::string val, char quote)
{
	this->value = val;
	this->quoteType = quote;
}

char AttributeValueToken::getQuoteType()
{
	return quoteType;
}

void AttributeValueToken::setQuoteType(char quote)
{
	quoteType = quote;
}

void AttributeValueToken::print()
{
	std::cout << quoteType << value << quoteType << " ";
}

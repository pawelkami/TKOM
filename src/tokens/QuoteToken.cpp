#include "QuoteToken.h"
#include <iostream>

void QuoteToken::print()
{
	std::cout << "[QuoteToken              ] " << this->value << "\n";
}

TokenType QuoteToken::getType()
{
	return Quote;
}

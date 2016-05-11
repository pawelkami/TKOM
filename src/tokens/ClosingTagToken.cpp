#include "ClosingTagToken.h"
#include <iostream>


void ClosingTagToken::print()
{
	std::cout << "[ClosingTagToken         ] " << this->value << "\n";
}

TokenType ClosingTagToken::getType()
{
	return ClosingTag;
}

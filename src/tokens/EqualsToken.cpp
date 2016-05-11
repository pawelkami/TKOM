#include "EqualsToken.h"
#include <iostream>


void EqualsToken::print()
{
	std::cout << "[EqualsToken             ] " << this->value << "\n";
}

TokenType EqualsToken::getType()
{
	return Equals;
}

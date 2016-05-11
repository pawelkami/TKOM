#include "TextToken.h"
#include <iostream>

void TextToken::print()
{
	std::cout << "[TextToken               ] " << this->value << "\n";
}

TokenType TextToken::getType()
{
	return Text;
}

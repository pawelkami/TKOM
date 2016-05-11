#include "TagClosingMarkToken.h"
#include <iostream>

void TagClosingMarkToken::print()
{
	std::cout << "[TagClosingMarkToken     ] " << this->value << "\n";
}

TokenType TagClosingMarkToken::getType()
{
	return TagClosingMark;
}

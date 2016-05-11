#include "TagOpenerToken.h"
#include <iostream>

void TagOpenerToken::print()
{
	std::cout << "[TagOpenerToken          ] " << this->value << "\n";
}

TokenType TagOpenerToken::getType()
{
	return TagOpener;
}

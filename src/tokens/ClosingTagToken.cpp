#include "ClosingTagToken.h"
#include <iostream>

void ClosingTagToken::print()
{
	std::cout << "</" << this->value;
}

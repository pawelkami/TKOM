#include "ClosingTagToken.h"
#include <iostream>

void ClosingTagToken::print()
{
	std::cout << "[ClosingTagToken         ] " << "</" << this->value << "\n";
}

#include "DoctypeToken.h"
#include <iostream>

void DoctypeToken::print()
{
	std::cout << "<!doctype " << this->value << ">";
}

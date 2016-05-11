#include "DoctypeToken.h"
#include <iostream>

void DoctypeToken::print()
{
	std::cout << "[DoctypeToken            ] " << "<!" << this->value << "\n";
}



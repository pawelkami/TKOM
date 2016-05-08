#include "DoctypeToken.h"
#include <iostream>

void DoctypeToken::print()
{
	std::cout << "[DoctypeToken            ] " << "<!doctype " << this->value << ">" << "\n";
}



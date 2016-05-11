#include "EmptyClosingTagToken.h"
#include <iostream>

void EmptyClosingTagToken::print()
{
	std::cout << "[EmptyClosingTagToken    ] " <<  this->value << "\n";
}

TokenType EmptyClosingTagToken::getType()
{
	return EmptyClosingTag;
}

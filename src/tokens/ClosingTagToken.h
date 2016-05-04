#ifndef CLOSINGTAGTOKEN_H
#define CLOSINGTAGTOKEN_H

#include "Token.h"

// </tag
class ClosingTagToken : public Token
{
public:
	void print();
};

#endif
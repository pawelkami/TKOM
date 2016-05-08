#include "CommentToken.h"
#include <iostream>

void CommentToken::print()
{
	std::cout << "[CommentToken            ] " << "<!-- " + value + " -->" << "\n";
}


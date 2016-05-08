#include "TextPosition.h"

int TextPosition::getLineNumber()
{
	return lineNumber;
}

int TextPosition::getCharNumber()
{
	return charNumber;
}

int TextPosition::getGlobalNumber()
{
	return globalNumber;
}

void TextPosition::setLineNumber(int ln)
{
	lineNumber = ln;
}

void TextPosition::setCharNumber(int cn)
{
	charNumber = cn;
}

void TextPosition::setGlobalNumber(int global)
{
	globalNumber = global;
}

void TextPosition::incrementGlobalNumber()
{
	++globalNumber;
}


void TextPosition::incrementLineNumber()
{
	++lineNumber;
	charNumber = 1;
}

void TextPosition::incrementCharNumber()
{
	++charNumber;
}

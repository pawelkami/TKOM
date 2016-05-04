#include "TextPosition.h"

int TextPosition::getLineNumber()
{
	return lineNumber;
}

int TextPosition::getCharNumber()
{
	return charNumber;
}

void TextPosition::setLineNumber(int ln)
{
	lineNumber = ln;
}

void TextPosition::setCharNumber(int cn)
{
	charNumber = cn;
}

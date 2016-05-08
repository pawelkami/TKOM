#include "Token.h"

void Token::setValue(std::string value)
{
	this->value = value;
}

std::string Token::getValue()
{
	return value;
}

void Token::setTextPos(TextPosition pos)
{
	this->textPos = pos;
}

void Token::setTextPos(int ln, int cn)
{
	textPos = TextPosition(ln, cn);
}


TextPosition Token::getTextPosition()
{
	return textPos;
}

int Token::getLineNumber()
{
	return textPos.getLineNumber();
}

int Token::getCharNumber()
{
	return textPos.getCharNumber();
}

Token::Token()
{
}

Token::Token(std::string value)
{
	this->value = value;
}

Token::Token(std::string value, TextPosition pos)
{
	this->value = value;
	this->textPos = pos;
}

Token::Token(std::string value, int ln, int cn)
{
	this->value = value;
	this->textPos = TextPosition(ln, cn);
}

Token::Token(std::string value, int ln, int cn, int global)
{
	this->value = value;
	this->textPos.setLineNumber(ln);
	this->textPos.setCharNumber(cn);
	this->textPos.setGlobalNumber(global);
}

#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include "TextPosition.h"

class Token
{
protected:
	std::string value;
	TextPosition textPos;

public:
	Token();
	Token(std::string value);
	Token(std::string value, TextPosition pos);
	Token(std::string value, int ln, int cn);
	virtual ~Token() {}

	virtual void print() = 0;
	void setValue(std::string value);
	
	std::string getValue();

	void setTextPos(TextPosition pos);
	void setTextPos(int ln, int cn);

	TextPosition getTextPosition();
	int getLineNumber();
	int getCharNumber();


};

#endif
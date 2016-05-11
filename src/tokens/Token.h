#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include "TextPosition.h"

// enum mówi¹cy jakiego typu jest dany tag
enum TokenType 
{
	ClosingTag,
	Doctype,
	EmptyClosingTag,
	Equals,
	Text,
	TagClosingMark,
	TagOpener,
	Quote,
	None
};

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
	Token(std::string value, int ln, int cn, int global);
	virtual ~Token() {}

	virtual void print() = 0;
	void setValue(std::string value);
	
	std::string getValue();

	void setTextPos(TextPosition pos);
	void setTextPos(int ln, int cn);

	TextPosition getTextPosition();
	int getLineNumber();
	int getCharNumber();

	virtual TokenType getType();
};


#endif
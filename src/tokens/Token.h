#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include "TextPosition.h"

enum TokenType 
{
	AttributeKey,
	AttributeValue,
	ClosingTag,
	Comment,
	Doctype,
	EmptyClosingTag,
	Equals,
	PlainText,
	TagClosingMark,
	TagOpener,
	None
};

class Token
{
protected:
	std::string value;
	TextPosition textPos;

public:
	const TokenType type = None;

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
};


#endif
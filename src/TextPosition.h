#ifndef TEXTPOSITION_H
#define TEXTPOSITION_H


class TextPosition
{
private:
	int lineNumber;		// numer wiersza
	int charNumber;		// numer znaku w wierszu

public:
	TextPosition(int ln = 0, int cn = 0) : lineNumber(ln), charNumber(0) {}
	
	int getLineNumber();

	int getCharNumber();

	void setLineNumber(int ln);

	void setCharNumber(int cn);
};

#endif
#ifndef TEXTPOSITION_H
#define TEXTPOSITION_H

// Klasa reprezentuj�ca pozycj� w analizowanym tek�cie
class TextPosition
{
private:
	int lineNumber;		// numer wiersza
	int charNumber;		// numer znaku w wierszu
	int globalNumber;	// numer znaku w ca�ym tek�cie

public:
	// c-tor
	TextPosition(int ln = 1, int cn = 1, int global = 0) : lineNumber(ln), charNumber(cn), globalNumber(global) {}
	
	int getLineNumber();

	int getCharNumber();

	int getGlobalNumber();

	void setLineNumber(int ln);

	void setCharNumber(int cn);

	void setGlobalNumber(int global);

	void incrementGlobalNumber();

	void incrementLineNumber();

	void incrementCharNumber();
};

#endif
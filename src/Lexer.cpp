#include "Lexer.h"
#include <algorithm>
#include <string>
#include <iterator>
#include <locale>
#include <iostream>
#include <map>
#include "utils.h"

const std::string OPEN_COMMENT = "<!--";
const std::string CLOSE_COMMENT = "-->";


char Lexer::nextChar()
{
	if (textPos.getGlobalNumber() >= htmlString.size())
	{
		// koniec
		return EOF;
	}
	
	if (htmlString[textPos.getGlobalNumber()] == '\n')
	{
		textPos.incrementLineNumber();
	}
	else
	{
		textPos.incrementCharNumber();
	}

	textPos.incrementGlobalNumber();

	return htmlString[textPos.getGlobalNumber()-1];
}

char Lexer::getCurrentChar()
{
	if (textPos.getGlobalNumber() >= htmlString.size())
		return EOF;

	return htmlString[textPos.getGlobalNumber()];
}

void Lexer::skipWhitespaces()
{
	std::locale loc;
	while (isspace(getCurrentChar(), loc))
		nextChar();
}

bool Lexer::match(const std::string & toCompare)
{
	// jeśli słowo jest dłuższe niż nam pozostało znaków do końca
	if (textPos.getGlobalNumber() + toCompare.size() >= htmlString.size())
		return false;

	// sprawdzamy czy są równe
	if (compareCaseInsensitive(htmlString.substr(textPos.getGlobalNumber(), toCompare.size()), toCompare))
		return true;

	return false;
}

void Lexer::consumeChars(int n)
{
	for (int i = 0; i < n; ++i)
		nextChar();
}

std::string Lexer::getNextWord(char* bound)
{
	std::string word;
	char c;
	while ((c = getCurrentChar()) != EOF && !checkIfStringHasChar(bound, &c))
	{
		word.push_back(c);
		nextChar();
	}
	return word;
}

std::string Lexer::getNextWordWhitespaces(char* bound)
{
	std::string word;
	std::locale loc;
	char c;
	while ((c = getCurrentChar()) != EOF && !checkIfStringHasChar(bound, &c) && !isspace(c, loc))
	{
		word.push_back(c);
		nextChar();
	}
	return word;
}


std::string Lexer::printPosition()
{
	std::string pos = "";
	pos += "Line number: ";
	pos += std::to_string(textPos.getLineNumber());
	pos += " Column number: ";
	pos += std::to_string(textPos.getCharNumber());
	return pos;
}

bool Lexer::checkIfStringHasChar(const std::string& toCheck, const std::string& chars)
{
	for (auto& c : toCheck)
		for (auto& d : chars)
			if (c == d)
				return true;

	return false;
}

void Lexer::printAllTokens()
{
	for (auto& tok : listToken)
		tok->print();
}

Lexer::Lexer(const std::string& html)
{
	textPos = TextPosition();
	htmlString = html;
}

void Lexer::findAllTokens()
{

	while (textPos.getGlobalNumber() < htmlString.size() && getCurrentChar() != EOF)
	{
		listToken.push_back(getNextToken());
	}
}


PToken Lexer::getNextToken()
{
	std::locale loc;	// potrzebne żeby isspace nie miał problemów z analizowaniem znaków innych niż ascii
	// komentarze i koniec pliku
	do
	{
		skipWhitespaces();
		if (getCurrentChar() == EOF)
			return PToken(new EOFToken(textPos.getLineNumber(), textPos.getLineNumber(), textPos.getGlobalNumber()));
		else if (match(OPEN_COMMENT)) // obsługa komentarza
		{
			consumeChars(OPEN_COMMENT.size());	// przesuwamy się za <!--
			
			// zgarniamy cały komentarz
			do {
				nextChar();
			} while (!match(CLOSE_COMMENT) || getCurrentChar() == EOF);
			
			// jeśli nie został zamknięty komentarz to rzucamy wyjątek
			if (getCurrentChar() == EOF)
				throw std::runtime_error("Expected end of comment " + printPosition());

			consumeChars(CLOSE_COMMENT.size());	// przesuwamy się za -->
		}
		

	} while (isspace(getCurrentChar(), loc) || match(OPEN_COMMENT));

	TextPosition atompos(textPos);

	char c = getCurrentChar();


	// znaki terminalne
	switch (c)
	{
		case '<':
			atompos = textPos;
			nextChar();
			if (getCurrentChar() == '!')
			{
				if (match("!doctype"))
				{
					consumeChars(std::string("!doctype").size());
					return PToken(new DoctypeToken("doctype", atompos));
				}
				else
				{
					throw std::runtime_error("Expected doctype element " + printPosition());
				}
			}
			else if( getCurrentChar() == '/')
			{
				nextChar();
				return PToken(new ClosingTagToken(atompos));
			}

			return PToken(new TagOpenerToken(atompos));

		case '>':
			nextChar();
			return PToken(new TagClosingMarkToken(atompos));

		case '/':
			nextChar();
			if (getCurrentChar() == '>')
				return PToken(new EmptyClosingTagToken(atompos));
			return PToken(new TextToken("/", atompos));

		case '"':
			nextChar();
			return PToken(new QuoteToken(atompos));

		case '=':
			nextChar();
			return PToken(new EqualsToken(atompos));

		case EOF:
			return PToken(new EOFToken(atompos));
	}	
	
	// słowa
	std::string word = getNextWordWhitespaces("<>/\"=");
	return PToken(new TextToken(word, atompos));
}


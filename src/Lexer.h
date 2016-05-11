#ifndef LEXER_H
#define LEXER_H

#include "TextPosition.h"
#include "tokens/Token.h"
#include "tokens/ClosingTagToken.h"
#include "tokens/DoctypeToken.h"
#include "tokens/EmptyClosingTagToken.h"
#include "tokens/EqualsToken.h"
#include "tokens/TagClosingMarkToken.h"
#include "tokens/TagOpenerToken.h"
#include "tokens/QuoteToken.h"
#include "tokens/EOFToken.h"
#include "tokens/TextToken.h"
#include <list>
#include <stack>
#include "Tags.h"
#include <memory>

// sprytny wska�nik na Token
typedef std::shared_ptr<Token> PToken;

// Klasa Lexera
class Lexer
{
private:
	// aktualna pozycja w analizowanym tek�cie
	TextPosition textPos;

	// lista token�w
	std::list<PToken> listToken;

	// analizowany tekst
	std::string htmlString;

	// metoda przechodz�ca do nast�pnego znaku, zwraca znak przed inkrementacj�
	char nextChar();

	// metoda zwracaj�ca aktualny znak
	char getCurrentChar();

	// metoda omijaj�ca bia�e znaki
	void skipWhitespaces();

	// funkcja sprawdzaj�ca czy s�owo le��ce od aktualnej pozycji pasuje do s�owa z argumentu
	bool match(const std::string& toCompare);

	// przesuni�cie o n ci�gu wej�ciowego
	void consumeChars(int n);

	// metoda szuka s�owa a� do znak�w zdefiniowanych w argumencie
	std::string getNextWord(char* bound);

	// metoda szuka s�owa a� do znak�w zdefiniowancych w argumencie lub do bia�ego znaku
	std::string getNextWordWhitespaces(char* bound);


	// metoda sprawdzaj�ca czy pierwszy argument posiada jakis znak z argumentu 2
	bool checkIfStringHasChar(const std::string& toCheck, const std::string& chars);

public:
	// html - string reprezentuj�cy badany plik
	Lexer(std::string html);

	// funkcja znajduj�ca wszystkie tokeny
	void findAllTokens();

	// metoda zwracaj�ca kolejny token
	PToken getNextToken();

	// metoda wypisuj�ca z listy wszystkie znalezione tokeny
	void printAllTokens();

	// metoda zwracaj�ca ci�g znak�w m�wi�cy o aktualnej pozycji w badanym tek�cie,
	// u�ywana przy wy�wietlaniu informacji o b��dzie
	std::string printPosition();
};

#endif

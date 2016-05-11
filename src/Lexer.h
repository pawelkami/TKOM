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

// sprytny wskaŸnik na Token
typedef std::shared_ptr<Token> PToken;

// Klasa Lexera
class Lexer
{
private:
	// aktualna pozycja w analizowanym tekœcie
	TextPosition textPos;

	// lista tokenów
	std::list<PToken> listToken;

	// analizowany tekst
	std::string htmlString;

	// metoda przechodz¹ca do nastêpnego znaku, zwraca znak przed inkrementacj¹
	char nextChar();

	// metoda zwracaj¹ca aktualny znak
	char getCurrentChar();

	// metoda omijaj¹ca bia³e znaki
	void skipWhitespaces();

	// funkcja sprawdzaj¹ca czy s³owo le¿¹ce od aktualnej pozycji pasuje do s³owa z argumentu
	bool match(const std::string& toCompare);

	// przesuniêcie o n ci¹gu wejœciowego
	void consumeChars(int n);

	// metoda szuka s³owa a¿ do znaków zdefiniowanych w argumencie
	std::string getNextWord(char* bound);

	// metoda szuka s³owa a¿ do znaków zdefiniowancych w argumencie lub do bia³ego znaku
	std::string getNextWordWhitespaces(char* bound);


	// metoda sprawdzaj¹ca czy pierwszy argument posiada jakis znak z argumentu 2
	bool checkIfStringHasChar(const std::string& toCheck, const std::string& chars);

public:
	// html - string reprezentuj¹cy badany plik
	Lexer(std::string html);

	// funkcja znajduj¹ca wszystkie tokeny
	void findAllTokens();

	// metoda zwracaj¹ca kolejny token
	PToken getNextToken();

	// metoda wypisuj¹ca z listy wszystkie znalezione tokeny
	void printAllTokens();

	// metoda zwracaj¹ca ci¹g znaków mówi¹cy o aktualnej pozycji w badanym tekœcie,
	// u¿ywana przy wyœwietlaniu informacji o b³êdzie
	std::string printPosition();
};

#endif

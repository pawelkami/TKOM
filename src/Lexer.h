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
typedef std::unique_ptr<Token> PToken;

// Klasa Lexera
class Lexer
{
private:
	// aktualna pozycja w analizowanym tekœcie
	TextPosition textPos;

	// lista tokenów
	std::list<PToken> listToken;

	// stos do sprawdzania poprawnoœci kolejnoœci tokenów
	std::stack<std::string> stack;

	// analizowany tekst
	std::string htmlString;

	// usuniêcie elementu ze szczytu stosu oraz porównanie go z podanym w argumencie tagiem
	// jeœli s¹ ró¿ne to zostaje rzucony wyj¹tek spowodowany z³¹ kolejnoœci¹ tagów w pliku
	void popStack(const std::string& tag);

	// wrzucenie tagu podawanego w argumencie na szczyt stosu
	void pushStack(const std::string& tag);

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

	// porównywanie stringów bez wzglêdu na wielkoœæ litery
	bool compareCaseInsensitive(const std::string& str1, const std::string& str2);

	// metoda pomocnicza, s³u¿y do zamienienia wszystkich znaków w stringu na ma³e
	std::string makeLowerCase(const std::string& in);

	// metoda sprawdzaj¹ca czy tag podany w argumencie jest prawid³owym tagiem w HTML
	void checkTag(const std::string& tag);

	// metoda sprawdzaj¹ca czy tag podany w argumencie jest tagiem pojedynczym(nie wymagaj¹cym zamkniêcia)
	bool checkTagSingle(const std::string& tag);

	// metoda zwracaj¹ca ci¹g znaków mówi¹cy o aktualnej pozycji w badanym tekœcie,
	// u¿ywana przy wyœwietlaniu informacji o b³êdzie
	std::string printPosition();

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
};

#endif

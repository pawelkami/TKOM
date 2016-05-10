#ifndef LEXER_H
#define LEXER_H

#include "TextPosition.h"
#include "tokens/Token.h"
#include "tokens/AttributeKeyToken.h"
#include "tokens/AttributeValueToken.h"
#include "tokens/ClosingTagToken.h"
#include "tokens/CommentToken.h"
#include "tokens/DoctypeToken.h"
#include "tokens/EmptyClosingTagToken.h"
#include "tokens/EqualsToken.h"
#include "tokens/PlainTextToken.h"
#include "tokens/TagClosingMarkToken.h"
#include "tokens/TagOpenerToken.h"
#include <list>
#include <stack>
#include "Tags.h"
#include <memory>

// sprytny wska�nik na Token
typedef std::unique_ptr<Token> PToken;

// Klasa Lexera
class Lexer
{
private:
	// aktualna pozycja w analizowanym tek�cie
	TextPosition textPos;

	// lista token�w
	std::list<PToken> listToken;

	// stos do sprawdzania poprawno�ci kolejno�ci token�w
	std::stack<std::string> stack;

	// analizowany tekst
	std::string htmlString;

	// usuni�cie elementu ze szczytu stosu oraz por�wnanie go z podanym w argumencie tagiem
	// je�li s� r�ne to zostaje rzucony wyj�tek spowodowany z�� kolejno�ci� tag�w w pliku
	void popStack(const std::string& tag);

	// wrzucenie tagu podawanego w argumencie na szczyt stosu
	void pushStack(const std::string& tag);

	// metoda przechodz�ca do nast�pnego znaku, zwraca znak przed inkrementacj�
	char nextChar();

	// metoda zwracaj�ca aktualny znak
	char getCurrentChar();

	// metoda omijaj�ca bia�e znaki
	void skipWhitespaces();

	// metoda szuka s�owa a� do znak�w zdefiniowanych w argumencie
	std::string getNextWord(char* bound);

	// metoda szuka s�owa a� do znak�w zdefiniowancych w argumencie lub do bia�ego znaku
	std::string getNextWordWhitespaces(char* bound);

	// por�wnywanie string�w bez wzgl�du na wielko�� litery
	bool compareCaseInsensitive(const std::string& str1, const std::string& str2);

	// metoda pomocnicza, s�u�y do zamienienia wszystkich znak�w w stringu na ma�e
	std::string makeLowerCase(const std::string& in);

	// metoda szukaj�ca doctype
	void findDoctype();

	// metoda oczekuj�ca komentarza
	void expectComment();

	// metoda oczekuj�ca zamkni�ca tagu
	void expectCloseTag();

	// metoda oczekuj�ca s�owa w podw�jnym cudzys�owie
	void expectDoubleQuotes();

	// metoda oczekuj�ca s�owa w apostrofach
	void expectSingleQuote();

	// metoda zajmuj�ca si� tagiem script
	void handleScriptTag();

	// metoda analizuj�ca ci�g znak�w pomi�dzy < i /> lub < i >
	void analyzeInnerTag();

	// metoda sprawdzaj�ca czy tag podany w argumencie jest prawid�owym tagiem w HTML
	void checkTag(const std::string& tag);

	// metoda sprawdzaj�ca czy tag podany w argumencie jest tagiem pojedynczym(nie wymagaj�cym zamkni�cia)
	bool checkTagSingle(const std::string& tag);

	// metoda zwracaj�ca ci�g znak�w m�wi�cy o aktualnej pozycji w badanym tek�cie,
	// u�ywana przy wy�wietlaniu informacji o b��dzie
	std::string printPosition();

	// metoda sprawdzaj�ca czy pierwszy argument posiada jakis znak z argumentu 2
	bool checkIfStringHasChar(const std::string& toCheck, const std::string& chars);

public:
	// html - string reprezentuj�cy badany plik
	Lexer(std::string html);

	// funkcja znajduj�ca wszystkie tokeny
	void findAllTokens();

	// funkcja szukaj�ca kolejnego tokenu
	void nextToken();

	// metoda wypisuj�ca z listy wszystkie znalezione tokeny
	void printAllTokens();
};

#endif

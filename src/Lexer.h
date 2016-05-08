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


typedef std::unique_ptr<Token> PToken;

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

	void popStack(const std::string& tag);

	void pushStack(const std::string& tag);

	// metoda przechodz¹ca do nastêpnego znaku
	char nextChar();

	// metoda zwracaj¹ca aktualny znak
	char getCurrentChar();

	// metoda omijaj¹ca bia³e znaki
	void skipWhitespaces();

	// metoda szuka s³owa a¿ do znaków zdefiniowanych w argumencie
	std::string getNextWord(char* bound);

	// metoda szuka s³owa a¿ do znaków zdefiniowancych w argumencie lub do bia³ego znaku
	std::string getNextWordWhitespaces(char* bound);

	// porównywanie stringów bez wzglêdu na wielkoœæ litery
	bool compareCaseInsensitive(const std::string& str1, const std::string& str2);

	std::string makeLowerCase(const std::string& in);

	void findDoctype();

	void expectComment();

	void expectCloseTag();

	void expectDoubleQuotes();

	void expectSingleQuote();

	void handleScriptTag();

	void analyzeInnerTag();

	void checkTag(const std::string& tag);

	bool checkTagSingle(const std::string& tag);

	std::string printPosition();

	// metoda sprawdzaj¹ca czy pierwszy argument posiada jakis znak z argumentu 2
	bool checkIfStringHasChar(const std::string& toCheck, const std::string& chars);

public:
	Lexer(std::string html);

	void findAllTokens();

	void nextToken();

	// metoda wypisuj¹ca z listy wszystkie znalezione tokeny
	void printAllTokens();
};

#endif

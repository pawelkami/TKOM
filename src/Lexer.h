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
	// aktualna pozycja w analizowanym tek�cie
	TextPosition textPos;

	// lista token�w
	std::list<PToken> listToken;

	// stos do sprawdzania poprawno�ci kolejno�ci token�w
	std::stack<std::string> stack;

	// analizowany tekst
	std::string htmlString;

	void popStack(const std::string& tag);

	void pushStack(const std::string& tag);

	// metoda przechodz�ca do nast�pnego znaku
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

	// metoda sprawdzaj�ca czy pierwszy argument posiada jakis znak z argumentu 2
	bool checkIfStringHasChar(const std::string& toCheck, const std::string& chars);

public:
	Lexer(std::string html);

	void findAllTokens();

	void nextToken();

	// metoda wypisuj�ca z listy wszystkie znalezione tokeny
	void printAllTokens();
};

#endif

#ifndef PARSER_H
#define PARSER_H

#include "Lexer.h"
#include "Tags.h"
#include "elements/HtmlElement.h"
#include <stack>
#include "utils.h"

class Parser
{
private:
	Lexer lexer;
	
	PHtmlElement root;
	PToken actToken;
	std::stack<PHtmlElement> stack;

	void handleDoctype();

	void handleScript();

	void handleClosingTag();

	void analyzeAttributes(PHtmlElement& el);

	std::string handleQuote();

	void nextToken();
	
	PHtmlElement parseTag();

	// metoda sprawdzaj�ca czy tag podany w argumencie jest prawid�owym tagiem w HTML
	void checkTag(const std::string& tag);

	// metoda sprawdzaj�ca czy tag podany w argumencie jest tagiem pojedynczym(nie wymagaj�cym zamkni�cia)
	bool checkTagSingle(const std::string& tag);

	// usuni�cie elementu ze szczytu stosu oraz por�wnanie go z podanym w argumencie tagiem
	// je�li s� r�ne to zostaje rzucony wyj�tek spowodowany z�� kolejno�ci� tag�w w pliku
	void popStack(const std::string& tag);

	// wrzucenie tagu podawanego w argumencie na szczyt stosu
	void pushStack(PHtmlElement& tag);
public:
	Parser(const std::string& html);

	void parse();

	PHtmlElement& getRoot();


};

#endif
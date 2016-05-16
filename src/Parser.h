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

	// metoda sprawdzaj¹ca czy tag podany w argumencie jest prawid³owym tagiem w HTML
	void checkTag(const std::string& tag);

	// metoda sprawdzaj¹ca czy tag podany w argumencie jest tagiem pojedynczym(nie wymagaj¹cym zamkniêcia)
	bool checkTagSingle(const std::string& tag);

	// usuniêcie elementu ze szczytu stosu oraz porównanie go z podanym w argumencie tagiem
	// jeœli s¹ ró¿ne to zostaje rzucony wyj¹tek spowodowany z³¹ kolejnoœci¹ tagów w pliku
	void popStack(const std::string& tag);

	// wrzucenie tagu podawanego w argumencie na szczyt stosu
	void pushStack(PHtmlElement& tag);
public:
	Parser(const std::string& html);

	void parse();

	PHtmlElement& getRoot();


};

#endif
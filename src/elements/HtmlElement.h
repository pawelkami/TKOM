#ifndef HTMLELEMENT_H
#define HTMLELEMENT_H

#include <string>
#include <list>
#include "HtmlAttribute.h"
#include <memory>

class HtmlElement;

typedef std::shared_ptr<HtmlElement> PHtmlElement;

class HtmlElement
{
public:
	HtmlElement();
	~HtmlElement();

	std::string tag;
	
	// plain text le¿¹cy w elemencie
	std::string text;

	// lista wskaŸników na elementy le¿¹ce wewn¹trz danego tagu
	std::list<PHtmlElement> children;

	// lista atrybutów
	std::list<HtmlAttribute> attributes;

	bool parsed;
};

#endif
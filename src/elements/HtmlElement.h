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
	
	// plain text le��cy w elemencie
	std::string text;

	// lista wska�nik�w na elementy le��ce wewn�trz danego tagu
	std::list<PHtmlElement> children;

	// lista atrybut�w
	std::list<HtmlAttribute> attributes;

	bool parsed;
};

#endif
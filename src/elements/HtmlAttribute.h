#ifndef HTMLATTRIBUTE_H
#define HTMLATTRIBUTE_H

#include <string>

class HtmlAttribute
{
public:
	HtmlAttribute(std::string n = "", std::string val = "") : name(n), value(val) {}
	~HtmlAttribute();

	// nazwa atrybutu
	std::string name;

	// wartoœæ atrybutu
	std::string value;
};

#endif
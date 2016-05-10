#ifndef TAGS_H
#define TAGS_H

#include <map>

// Klasa przetrzymuj�ca tagi wykorzystywane w HTML
class Tags
{
private:
	// mapa tag�w
	// std::string - nazwa tagu
	// bool - true je�li tag jest pojedynczy - nie wymaga zamkni�cia
	std::map<std::string, bool> mapTags;
	
	// c-tor
	Tags();
public:
	static Tags& getInstance();
	~Tags();

	// metoda sprawdzaj�ca czy istnieje dany tag
	bool checkIfTagExists(const std::string& tag);

	// metoda sprawdzaj�ca czy dany tag jest pojedynczy
	bool checkIfTagIsSingle(const std::string& tag);

};

#endif
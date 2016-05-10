#ifndef TAGS_H
#define TAGS_H

#include <map>

// Klasa przetrzymuj¹ca tagi wykorzystywane w HTML
class Tags
{
private:
	// mapa tagów
	// std::string - nazwa tagu
	// bool - true jeœli tag jest pojedynczy - nie wymaga zamkniêcia
	std::map<std::string, bool> mapTags;
	
	// c-tor
	Tags();
public:
	static Tags& getInstance();
	~Tags();

	// metoda sprawdzaj¹ca czy istnieje dany tag
	bool checkIfTagExists(const std::string& tag);

	// metoda sprawdzaj¹ca czy dany tag jest pojedynczy
	bool checkIfTagIsSingle(const std::string& tag);

};

#endif
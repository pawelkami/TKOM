#ifndef TAGS_H
#define TAGS_H

#include <map>


class Tags
{
private:
	std::map<std::string, bool> mapTags;
	Tags();
public:
	static Tags& getInstance();
	~Tags();

	// metoda sprawdzaj¹ca czy istnieje dany tag
	bool checkIfTagExists(const std::string& tag);

	bool checkIfTagIsSingle(const std::string& tag);

};

#endif
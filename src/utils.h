#ifndef UTILS_H
#define UTILS_H
#include <string>

// por�wnywanie string�w bez wzgl�du na wielko�� litery
bool compareCaseInsensitive(const std::string& str1, const std::string& str2);

// metoda pomocnicza, s�u�y do zamienienia wszystkich znak�w w stringu na ma�e
std::string makeLowerCase(const std::string& in);

std::string trimWhitespaces(const std::string& str);

std::string replaceSpaces(const std::string& str);



#endif
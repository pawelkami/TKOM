#ifndef UTILS_H
#define UTILS_H
#include <string>

// porównywanie stringów bez wzglêdu na wielkoœæ litery
bool compareCaseInsensitive(const std::string& str1, const std::string& str2);

// metoda pomocnicza, s³u¿y do zamienienia wszystkich znaków w stringu na ma³e
std::string makeLowerCase(const std::string& in);



#endif
#ifndef RESULTSANALYZER_H
#define RESULTSANALYZER_H

#include "Parser.h"

class ResultsAnalyzer
{
private:
	PHtmlElement root;


	// funkcja wypisuj¹ca podstawowe informacje o pliku
	void getBasicInfo();

	// funkcja wypisuj¹ca listê antywirusów
	void getAntyvirList();
public:
	ResultsAnalyzer(PHtmlElement& r) : root(r) {}
	~ResultsAnalyzer();

	void analyze();
};

#endif

#ifndef RESULTSANALYZER_H
#define RESULTSANALYZER_H

#include "Parser.h"

class ResultsAnalyzer
{
private:
	PHtmlElement root;


	// funkcja wypisuj�ca podstawowe informacje o pliku
	void getBasicInfo();

	// funkcja wypisuj�ca list� antywirus�w
	void getAntyvirList();
public:
	ResultsAnalyzer(PHtmlElement& r) : root(r) {}
	~ResultsAnalyzer();

	void analyze();
};

#endif

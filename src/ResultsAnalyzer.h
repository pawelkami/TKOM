#ifndef RESULTSANALYZER_H
#define RESULTSANALYZER_H

#include "Parser.h"

class ResultsAnalyzer
{
private:
	PHtmlElement root;


	PHtmlElement findElement(const std::string& attr, const std::string& value);
public:
	// funkcja wypisuj�ca podstawowe informacje o pliku
	void getBasicInfo();

	// funkcja wypisuj�ca list� antywirus�w
	void getAntyvirList();
	
	ResultsAnalyzer(PHtmlElement& r) : root(r) {}
	~ResultsAnalyzer();

	void analyze();
};

#endif

#ifndef RESULTSANALYZER_H
#define RESULTSANALYZER_H

#include "Parser.h"

class ResultsAnalyzer
{
private:
	PHtmlElement root;

	PHtmlElement findElement(const std::string& attr, const std::string& value);

	PHtmlElement findElement(const std::string& attr, const std::string& value, const PHtmlElement& begin);

public:
	// funkcja wypisuj¹ca podstawowe informacje o pliku
	std::string getBasicInfo();

	// funkcja wypisuj¹ca listê antywirusów
	std::string getAntyvirList();

	std::string getSHA();

	std::string getFilename();

	std::string getDetectionRatio();

	std::string getAnalysisDate();

	std::string getFileDetails();

	std::string getMetadata();
	
	ResultsAnalyzer(PHtmlElement& r) : root(r) {}
	
	~ResultsAnalyzer();

	void analyze();
};

#endif

#ifndef RESULTSANALYZER_H
#define RESULTSANALYZER_H

#include "Parser.h"

class ResultsAnalyzer
{
private:
	PHtmlElement root;

	PHtmlElement findElement(const std::string& attr, const std::string& value);

	PHtmlElement findElement(const std::string& attr, const std::string& value, const PHtmlElement& begin);

	std::string getKeyName(const std::string& key);

	std::string getValueName(const std::string& val);

	std::string makeJsonKeyValue(const std::string& key, const std::string& val, bool isValueJson=false);

    std::string makeJsonList(const std::string& str);


public:
	std::string makeJson(const std::string& str);

	// funkcja wypisuj�ca podstawowe informacje o pliku
	std::string getBasicInfo();

	// funkcja wypisuj�ca list� antywirus�w
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

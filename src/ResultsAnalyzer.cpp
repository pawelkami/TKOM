#include "ResultsAnalyzer.h"
#include <iostream>
#include <iomanip>
#include <stack>
#include <sstream>

using namespace std;


PHtmlElement ResultsAnalyzer::findElement(const std::string& attr, const std::string& value)
{
	stack<PHtmlElement> stack;
	stack.push(root);
	while (!stack.empty())
	{
		auto el = stack.top();
		stack.pop();

		// sprawdzamy czy ten element pasuje to naszego wzorca
		for (auto& a : el->attributes)
		{
			if (a.name == attr && a.value == value)
				return el;
		}
		for (auto& ch : el->children)
			stack.push(ch);
	}

	return PHtmlElement();
}

std::string ResultsAnalyzer::getBasicInfo()
{
	// <div id="basic-info">
	
	auto basicInfo = findElement("id", "basic-info");
	stringstream ss;
	
	if (basicInfo)
	{
		basicInfo = basicInfo->children[0]->children[0]->children[0]->children[0];
		// SHA
		ss << basicInfo->children[0]->children[0]->text << basicInfo->children[0]->children[1]->text << endl;

		// nazwa pliku
		ss << basicInfo->children[1]->children[0]->text << basicInfo->children[1]->children[1]->text << endl;

		// wspó³czynnik wykrycia
		ss << basicInfo->children[2]->children[0]->text << basicInfo->children[2]->children[1]->text << endl;

		// data analizy
		ss << basicInfo->children[3]->children[0]->text << basicInfo->children[3]->children[1]->text << endl;
	}

	return ss.str();


}

std::string ResultsAnalyzer::getAntyvirList()
{
	auto results = findElement("id", "antivirus-results");
	stringstream ss;

	if (results)
	{
		ss << setw(21) << "Antywirus" << setw(32) << "Nazwa wykryta" << setw(14) << "Data analizy" << endl;
		for (auto& c : results->children[1]->children)
		{
			if (c->children[1]->attributes[0].value.find("green") != std::string::npos)
				ss << setw(21) << c->children[0]->text << setw(32) << "File not detected" << setw(14) << c->children[2]->text << endl;
			else
				ss << setw(21) << c->children[0]->text << setw(32) << c->children[1]->text << setw(14) << c->children[2]->text << endl;
	
		}
	}

	return ss.str();
}

std::string ResultsAnalyzer::getSHA()
{
	auto basicInfo = findElement("id", "basic-info");
	stringstream ss;

	if (basicInfo)
	{
		basicInfo = basicInfo->children[0]->children[0]->children[0]->children[0];
		// SHA
		ss << basicInfo->children[0]->children[0]->text << basicInfo->children[0]->children[1]->text << endl;
	}

	return ss.str();
}

std::string ResultsAnalyzer::getFilename()
{
	auto basicInfo = findElement("id", "basic-info");
	stringstream ss;

	if (basicInfo)
	{
		basicInfo = basicInfo->children[0]->children[0]->children[0]->children[0];
		// nazwa pliku
		ss << basicInfo->children[1]->children[0]->text << basicInfo->children[1]->children[1]->text << endl;
	}

	return ss.str();
}

std::string ResultsAnalyzer::getDetectionRatio()
{
	auto basicInfo = findElement("id", "basic-info");
	stringstream ss;

	if (basicInfo)
	{
		basicInfo = basicInfo->children[0]->children[0]->children[0]->children[0];
		// detection ratio
		ss << basicInfo->children[2]->children[0]->text << basicInfo->children[2]->children[1]->text << endl;
	}

	return ss.str();

}

std::string ResultsAnalyzer::getAnalysisDate()
{
	auto basicInfo = findElement("id", "basic-info");
	stringstream ss;

	if (basicInfo)
	{
		basicInfo = basicInfo->children[0]->children[0]->children[0]->children[0];
		// analysis date
		ss << basicInfo->children[3]->children[0]->text << basicInfo->children[3]->children[1]->text << endl;
	}

	return ss.str();
}

ResultsAnalyzer::~ResultsAnalyzer()
{
}

void ResultsAnalyzer::analyze()
{
	cout << getBasicInfo();
	cout << endl;
	cout << getAntyvirList();
}

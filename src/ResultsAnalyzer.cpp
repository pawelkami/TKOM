#include "ResultsAnalyzer.h"
#include <iostream>
#include <iomanip>
#include <stack>

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

void ResultsAnalyzer::getBasicInfo()
{
	// <div id="basic-info">
	
	auto basicInfo = findElement("id", "basic-info");
	
	if (basicInfo)
	{
		basicInfo = basicInfo->children[0]->children[0]->children[0]->children[0];
		// SHA
		cout << basicInfo->children[0]->children[0]->text << basicInfo->children[0]->children[1]->text << endl;

		// nazwa pliku
		cout << basicInfo->children[1]->children[0]->text << basicInfo->children[1]->children[1]->text << endl;

		// wspó³czynnik wykrycia
		cout << basicInfo->children[2]->children[0]->text << basicInfo->children[2]->children[1]->text << endl;

		// data analizy
		cout << basicInfo->children[3]->children[0]->text << basicInfo->children[3]->children[1]->text << endl;
	}


}

void ResultsAnalyzer::getAntyvirList()
{
	auto results = findElement("id", "antivirus-results");
	
	if (results)
	{
		cout << setw(21) << "Antywirus" << setw(32) << "Nazwa wykryta" << setw(14) << "Data analizy" << endl;
		for (auto& c : results->children[1]->children)
		{
			if (c->children[1]->attributes[0].value.find("green") != std::string::npos)
				cout << setw(21) << c->children[0]->text << setw(32) << "File not detected" << setw(14) << c->children[2]->text << endl;
			else
				cout << setw(21) << c->children[0]->text << setw(32) << c->children[1]->text << setw(14) << c->children[2]->text << endl;
	
		}
	}
}

ResultsAnalyzer::~ResultsAnalyzer()
{
}

void ResultsAnalyzer::analyze()
{
	getBasicInfo();
	cout << endl;
	getAntyvirList();
}

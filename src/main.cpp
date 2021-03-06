#include <iostream>
#include <fstream>
#include "Lexer.h"
#include "Parser.h"
#include "ResultsAnalyzer.h"

using namespace std;

// funkcja do czytania wej�ciowego pliku html
void readData(string& html, const string& path)
{
	ifstream ifs(path);
	while (!ifs.eof())
	{
		string tmp;
		getline(ifs, tmp);
		tmp += "\n";
		html += tmp;
	}
}


int main(int argc, char** argv)
{
	if (argc != 2)
	{
		cout << "Usage:" << endl
			<< "./TKOM filename" << endl;
		return 1;
	}
	string html;
	readData(html, argv[1]);

	Lexer lexer = Lexer(html);

	try
	{
		Parser parser(html);
		parser.parse();

		ResultsAnalyzer analyzer(parser.getRoot());
		cout << "{" << endl;
		cout << analyzer.getBasicInfo() << endl;
		cout << analyzer.getFileDetails() << endl;
		cout << analyzer.getMetadata() << endl;
		cout << analyzer.getAntyvirList() << endl;
		cout << "}";
	}
	catch (const runtime_error& e)
	{
		cout << e.what() << endl;
	}


	return 0;
}

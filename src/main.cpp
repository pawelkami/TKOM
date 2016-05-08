#include <iostream>
#include "Lexer.h"

using namespace std;

string html = "<!doctype><html>aaaa<body><div>aaadasd</div></body></html>";

// funkcja do czytania wejœciowego pliku html
string readData()
{
	string html;
	while (!cin.eof())
	{
		string tmp;
		getline(cin, tmp);
		tmp += "\n";
		html += tmp;
	}

	return html;
}


int main(int argc, char** argv)
{
	html = readData();
	Lexer lexer = Lexer(html);

	try
	{
		lexer.findAllTokens();
		lexer.printAllTokens();
	}
	catch (exception e)
	{
		cout << e.what();
	}

	return 0;
}
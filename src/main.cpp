#include <iostream>
#include "Lexer.h"

using namespace std;

// funkcja do czytania wej�ciowego pliku html
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
	string html = readData();

	Lexer lexer = Lexer(html);

	try
	{
		lexer.findAllTokens();
		lexer.printAllTokens();
	}
	catch (const runtime_error& e)
	{
		cout << e.what() << endl;
	}


	return 0;
}

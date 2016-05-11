#include <iostream>
#include "Lexer.h"
#include "Parser.h"

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
	//string html = readData();
	string html = "<!doctype aaa><html><div></div>aaa</html>";
	//string html = "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">";
	Lexer lexer = Lexer(html);

	try
	{
		//lexer.findAllTokens();
		//lexer.printAllTokens();
		Parser parser(html);
		parser.parse();

	}
	catch (const runtime_error& e)
	{
		cout << e.what() << endl;
	}

	cin.get();
	return 0;
}

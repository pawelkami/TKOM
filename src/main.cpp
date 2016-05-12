#include <iostream>
#include <fstream>
#include "Lexer.h"
#include "Parser.h"

using namespace std;

// funkcja do czytania wej�ciowego pliku html
void readData(string& html)
{
	ifstream ifs("./test/testVirusTotal.html");
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
	string html;
	readData(html);
	//string html = "<!doctype aaa><html><div></div>aaa</html>";
	//string html = "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">";

	//ifstream ifs("./test/testVirusTotal.html");
	//getline(ifs, html, (char)ifs.eof());
	//Lexer lexer = Lexer(html);

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

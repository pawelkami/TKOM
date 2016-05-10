#include "Lexer.h"
#include "exceptions/EOFexception.h"
#include <algorithm>
#include <string>
#include <iterator>
#include <locale>
#include <iostream>

void Lexer::popStack(const std::string& tag)
{
	if (stack.top() != tag)
	{
		throw std::runtime_error("Bad order of tags - expected '" + stack.top() + "' and there is " + tag + " " + printPosition() + "\n");
	}
	stack.pop();
}

void Lexer::pushStack(const std::string& tag)
{
	stack.push(tag);
}

char Lexer::nextChar()
{
	if (textPos.getGlobalNumber() + 1 >= htmlString.size())
	{
		// koniec
		throw EOFexception();
	}
	
	if (htmlString[textPos.getGlobalNumber()] == '\n')
	{
		textPos.incrementLineNumber();
	}
	else
	{
		textPos.incrementCharNumber();
	}

	textPos.incrementGlobalNumber();

	return htmlString[textPos.getGlobalNumber()-1];
}

char Lexer::getCurrentChar()
{
	return htmlString[textPos.getGlobalNumber()];
}

void Lexer::skipWhitespaces()
{
	std::locale loc;
	while (isspace(getCurrentChar(), loc))
		nextChar();
}

std::string Lexer::getNextWord(char* bound)
{
	std::string word;
	char c;
	while ((c = getCurrentChar()) && !checkIfStringHasChar(bound, &c))
	{
		word.push_back(c);
		nextChar();
	}
	return word;
}

std::string Lexer::getNextWordWhitespaces(char* bound)
{
	std::string word;
	std::locale loc;
	char c;
	while ((c = getCurrentChar()) && !checkIfStringHasChar(bound, &c) && !isspace(c, loc))
	{
		word.push_back(c);
		nextChar();
	}
	return word;
}

bool Lexer::compareCaseInsensitive(const std::string& str1, const std::string& str2)
{
	if(str1.size() != str2.size())
		return false;

	return makeLowerCase(str1) == makeLowerCase(str2);
}

std::string Lexer::makeLowerCase(const std::string & in)
{
	std::string out;

	std::transform(in.begin(), in.end(), std::back_inserter(out), tolower);
	return out;
}

void Lexer::findDoctype()
{
	skipWhitespaces();

	if (nextChar() == '<' && nextChar() == '!')
	{
		std::string doctype = getNextWordWhitespaces(">");
		if (!compareCaseInsensitive(doctype, "doctype"))
		{
			throw std::runtime_error("No doctype element." + '\n');
		}

		skipWhitespaces();

		std::string value = getNextWord(">");
		nextChar();
		listToken.push_back(PToken(new DoctypeToken(value, textPos.getLineNumber(), textPos.getCharNumber(), textPos.getGlobalNumber())));
	}
}

void Lexer::expectComment()
{
	if (nextChar() != '-' || nextChar() != '-')
	{
		throw std::runtime_error("Expected comment tag " + printPosition());
	}

	std::string insideComment = "";
	// p�tla w kt�rej szukamy ko�ca( znak '>' mo�e wyst�pi� w komentarzu, wi�c nie mo�emy uzna� tego za koniec komentarza)
	while (true)
	{
		std::string word = getNextWord(">");
		insideComment += word;
		nextChar(); // >

		if (word.size() >= 2 && word[word.size() - 2] == '-' && word[word.size() - 1] == '-')
		{
			insideComment.substr(0, insideComment.size() - 2);
			break;
		}
		else
		{
			insideComment += '>';
		}

	}
	listToken.push_back(PToken(new CommentToken(insideComment, textPos.getLineNumber(), textPos.getCharNumber(), textPos.getGlobalNumber())));

}

void Lexer::expectCloseTag()
{
	std::string word = getNextWord(">");
	nextChar(); // >

	checkTag(word);
	popStack(word);

	listToken.push_back(PToken(new ClosingTagToken(word, textPos.getLineNumber(), textPos.getCharNumber(), textPos.getGlobalNumber())));
	listToken.push_back(PToken(new TagClosingMarkToken(">", textPos.getLineNumber(), textPos.getCharNumber(), textPos.getGlobalNumber())));
}

void Lexer::expectDoubleQuotes()
{
	std::string word = getNextWord("\"");

	if (getCurrentChar() != '\"')
	{
		throw std::runtime_error("Expected double quotes " + printPosition() + "\n");
	}

	nextChar();
	listToken.push_back(PToken(new AttributeValueToken(word, textPos.getLineNumber(), textPos.getCharNumber(), textPos.getGlobalNumber(), '\"')));
}

void Lexer::expectSingleQuote()
{
	std::string word = getNextWord("\'");

	if (getCurrentChar() != '\'')
	{
		throw std::runtime_error("Expected single quote " + printPosition() + "\n");
	}

	nextChar();
	listToken.push_back(PToken(new AttributeValueToken(word, textPos.getLineNumber(), textPos.getCharNumber(), textPos.getGlobalNumber(), '\'')));

}

void Lexer::handleScriptTag()
{
	std::string word = getNextWord("<");

	while (getCurrentChar() != '/' || htmlString.substr(textPos.getGlobalNumber()+1, 6) != "script")
	{
		word += "<";
		word += getNextWord("<");
		nextChar(); // mijamy <
	}

	nextChar();
	if (word.size() != 0)
		listToken.push_back(PToken(new CommentToken(word, textPos.getLineNumber(), textPos.getCharNumber(), textPos.getGlobalNumber())));

	expectCloseTag();
}

void Lexer::analyzeInnerTag()
{
	skipWhitespaces();
	std::string word = getNextWordWhitespaces("/>");	// szukamy nazwy tagu

	checkTag(word);

	if (!checkTagSingle(word))
	{
		pushStack(word);
	}

	//dodajemy tag do listy
	listToken.push_back(PToken(new TagOpenerToken(word, textPos.getLineNumber(), textPos.getCharNumber(), textPos.getGlobalNumber())));

	while (getCurrentChar() != '/' && getCurrentChar() != '>')
	{
		skipWhitespaces();

		std::string w = getNextWordWhitespaces("=/>");
		if (!w.empty())
			listToken.push_back(PToken(new AttributeKeyToken(w, textPos.getLineNumber(), textPos.getCharNumber(), textPos.getGlobalNumber())));

		if (getCurrentChar() == '=')
		{
			listToken.push_back(PToken(new EqualsToken("=", textPos.getLineNumber(), textPos.getCharNumber(), textPos.getGlobalNumber())));
			nextChar();

			skipWhitespaces();
			if (getCurrentChar() == '\"')
			{
				nextChar();
				expectDoubleQuotes();
			}
			else if (getCurrentChar() == '\'')
			{
				nextChar();
				expectSingleQuote();
			}

			skipWhitespaces();
		}
		
	}
	

}

void Lexer::checkTag(const std::string & tag)
{
	if (!Tags::getInstance().checkIfTagExists(tag))
	{
		throw std::runtime_error("Tag " + tag + " does not exist " + printPosition() + "\n");
	}

}

bool Lexer::checkTagSingle(const std::string & tag)
{
	return Tags::getInstance().checkIfTagIsSingle(makeLowerCase(tag));
}

std::string Lexer::printPosition()
{
	std::string pos = "";
	pos += "Line number: ";
	pos += std::to_string(textPos.getLineNumber());
	pos += " Column number: ";
	pos += std::to_string(textPos.getCharNumber());
	return pos;
}

bool Lexer::checkIfStringHasChar(const std::string& toCheck, const std::string& chars)
{
	for (auto& c : toCheck)
		for (auto& d : chars)
			if (c == d)
				return true;

	return false;
}

void Lexer::printAllTokens()
{
	for (auto& tok : listToken)
		tok->print();
}

Lexer::Lexer(std::string html)
{
	textPos = TextPosition();
	htmlString = html;
}

void Lexer::findAllTokens()
{
	findDoctype();

	while (textPos.getGlobalNumber() < htmlString.size() - 1)
	{

		nextToken();
	}
}

void Lexer::nextToken()
{
	try
	{
		skipWhitespaces();

		std::string word = getNextWord("<");

		if (!word.empty())
		{
			listToken.push_back(PToken(new PlainTextToken(word, textPos.getLineNumber(), textPos.getCharNumber(), textPos.getGlobalNumber())));
		}

		// jeste�my na znaku <
		nextChar();

		if (getCurrentChar() == '!')
		{
			nextChar();
			expectComment();
		}
		else if (getCurrentChar() == '/')	// </
		{
			nextChar();
			expectCloseTag();
		}
		else
		{
			analyzeInnerTag();

			if (getCurrentChar() == '>')
			{
				listToken.push_back(PToken(new TagClosingMarkToken(">", textPos.getLineNumber(), textPos.getCharNumber(), textPos.getGlobalNumber())));
			}
			else if (nextChar() == '/' && getCurrentChar() == '>')
			{
				listToken.push_back(PToken(new EmptyClosingTagToken("/>", textPos.getLineNumber(), textPos.getCharNumber(), textPos.getGlobalNumber())));
			}
			else
				throw std::runtime_error("Expected close tag " + printPosition());

			nextChar();
			if (stack.top() == "script")
			{
				handleScriptTag();
			}

		}
	}
	catch(EOFexception e)
	{

	}

}

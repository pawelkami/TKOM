#include "Parser.h"

void Parser::handleDoctype()
{
	nextToken();
	
	if (actToken->getType() != Doctype)
	{
		throw std::runtime_error("Expected doctype " + lexer.printPosition());
	}

	PHtmlElement el(new HtmlElement());
	
	analyzeAttributes(el);

	el->tag = "doctype";
	el->parsed = true; // doctype nie trzeba dodatkowo zamykaæ

	root->children.push_back(el);

}

void Parser::handleScript()
{
	do {
		nextToken();
	} while (actToken->getType() != ClosingTag && actToken->getType() != None);

	if (actToken->getType() == None)
		throw std::runtime_error("Unexpected end of file " + lexer.printPosition());

	handleClosingTag();
}

void Parser::handleClosingTag()
{
	nextToken();
	stack.top()->parsed = true;
	popStack(actToken->getValue());
	nextToken();
	if (actToken->getType() != TagClosingMark)
		throw std::runtime_error("Expected '>', found " + lexer.printPosition());
}

void Parser::analyzeAttributes(PHtmlElement& el)
{
	nextToken();
	
	while (actToken->getType() != TagClosingMark && actToken->getType() != EmptyClosingTag)
	{
		if (actToken->getType() == Quote)
		{
			std::string insideQuote = handleQuote();
			el->attributes.push_back(HtmlAttribute(insideQuote));
		}
		else if (actToken->getType() == Text)
		{
			std::string name = actToken->getValue();
			std::string value = "";

			nextToken();

			// name="value"
			if (actToken->getType() == Equals)
			{
				nextToken();
				if (actToken->getType() == Quote)
				{
					value = handleQuote();
				}
				else
					throw std::runtime_error("Expected \"value\" " + lexer.printPosition());

				el->attributes.push_back(HtmlAttribute(name, value));
			}
			else
			{
				el->attributes.push_back(HtmlAttribute(name));
			}

			//continue;	// poniewa¿ ju¿ robiliœmy nextToken
		}
		else if (actToken->getType() == None)
		{
			throw std::runtime_error("Unexpected end of file while analyzing attributes " + lexer.printPosition());
		}
		else
		{
			throw std::runtime_error("Expected attributes, found '" + actToken->getValue() + "' " + lexer.printPosition());
		}
		
		nextToken();
	}

	// tag zosta³ zamkniêty przez "/>" wiêc skoñczyliœmy go analizowaæ
	if (actToken->getType() == EmptyClosingTag)
		el->parsed = true;
}

std::string Parser::handleQuote()
{
	std::string ret;
	nextToken();

	// tak d³ugo jak tokeny typu tekst to ³¹czymy
	while (actToken->getType() != Quote && actToken->getType() != None)
	{
		ret += actToken->getValue();
		nextToken();
	}

	if (actToken->getType() != Quote)
	{
		throw std::runtime_error("Expected quote " + lexer.printPosition());
	}

	return ret;
}

void Parser::nextToken()
{
	actToken = lexer.getNextToken();
}

PHtmlElement Parser::parseTag()
{
	nextToken();
	PHtmlElement el = std::make_unique<HtmlElement>();
	
	if (actToken->getType() == Text)
	{
		checkTag(actToken->getValue());
		el->tag = actToken->getValue();

		analyzeAttributes(el);

		if (checkTagSingle(el->tag))
			el->parsed = true;

		// jeœli nie ma nic na stosie to dodajemy do dzieci roota
		if (stack.empty())
			root->children.push_back(el);
		
		if (!stack.empty())
			stack.top()->children.push_back(el);

		// jeœli tag nie jest samozamykaj¹cy lub nie napotkaliœmy na /> to zapamiêtujemy go na stosie
		if (!(el->parsed))
		{

			pushStack(el);
		}

	}
	else
	{
		throw std::runtime_error("Expected name of tag, found '" + actToken->getValue() + "' " + lexer.printPosition());
	}
	

	return el;
}

Parser::Parser(const std::string& html) : lexer(Lexer(html))
{
	root = std::make_unique<HtmlElement>();
}

void Parser::parse()
{
	handleDoctype();
	nextToken();

	while (actToken->getType() != None)
	{
		if (!stack.empty() && compareCaseInsensitive(stack.top()->tag, "script"))
		{
			handleScript();
		} 
		else if (actToken->getType() == TagOpener)
		{
			parseTag();
		}
		else if (actToken->getType() == Text)
		{
			std::string text;
			do {
				text += actToken->getValue();
				nextToken();
			} while (actToken->getType() == Text || actToken->getType() == Quote);
			
			if (stack.empty())
				root->text += text;
			else
				stack.top()->text += text;

			continue;	// bo nextToken() by³ w do while
		}
		else if (actToken->getType() == Doctype)
		{
			throw std::runtime_error("Another <!doctype> tag found " + lexer.printPosition());
		}
		else if (actToken->getType() == ClosingTag)
		{
			handleClosingTag();
		}
		else if (actToken->getType() == EmptyClosingTag)
		{
			throw std::runtime_error("Unexpected '/>' " + lexer.printPosition());
		}
		else if (actToken->getType() == Equals || actToken->getType() == Quote)
		{
			if (stack.empty())
				root->text += actToken->getValue();
			else
				stack.top()->text += actToken->getValue();
		}

		nextToken();

	}
}

void Parser::checkTag(const std::string & tag)
{
	if (!Tags::getInstance().checkIfTagExists(tag))
	{
		throw std::runtime_error("Tag " + tag + " does not exist " + lexer.printPosition() + "\n");
	}

}

bool Parser::checkTagSingle(const std::string & tag)
{
	return Tags::getInstance().checkIfTagIsSingle(makeLowerCase(tag));
}

void Parser::popStack(const std::string& tag)
{
	if (stack.top()->tag != tag)
	{
		throw std::runtime_error("Bad order of tags - expected '" + stack.top()->tag + "' and there is " + tag + " " +  lexer.printPosition() + "\n");
	}
	stack.pop();
}

void Parser::pushStack(PHtmlElement& el)
{
	stack.push(el);
}




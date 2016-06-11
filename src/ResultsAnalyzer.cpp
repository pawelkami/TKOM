#include "ResultsAnalyzer.h"
#include <iostream>
#include <iomanip>
#include <stack>
#include <sstream>
#include "utils.h"

using namespace std;


PHtmlElement ResultsAnalyzer::findElement(const std::string& attr, const std::string& value)
{
    return findElement(attr, value, root);
}

PHtmlElement ResultsAnalyzer::findElement(const std::string & attr, const std::string & value, const PHtmlElement & begin)
{
    stack<PHtmlElement> stack;
    stack.push(begin);
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
    std::string result = "";

    if (basicInfo)
    {
        basicInfo = basicInfo->children[0]->children[0]->children[0]->children[0];
        // SHA
        ss << makeJsonKeyValue(basicInfo->children[0]->children[0]->text, basicInfo->children[0]->children[1]->text) << endl;

        // nazwa pliku
        ss << makeJsonKeyValue(basicInfo->children[1]->children[0]->text, basicInfo->children[1]->children[1]->text) << endl;

        // wspó³czynnik wykrycia
        ss << makeJsonKeyValue(basicInfo->children[2]->children[0]->text, basicInfo->children[2]->children[1]->text) << endl;

        // data analizy
        ss << makeJsonKeyValue(basicInfo->children[3]->children[0]->text, basicInfo->children[3]->children[1]->text) << endl;

        result = makeJsonKeyValue("basic_info", makeJson(ss.str()), true);
    }

    return result;


}

std::string ResultsAnalyzer::getAntyvirList()
{
    auto results = findElement("id", "antivirus-results");
    stringstream ss;
    string result = "";
    if (results)
    {
        for (auto& c : results->children[1]->children)
        {
            if (c->children[1]->attributes[0].value.find("green") != std::string::npos)
            {
                ss << makeJson(makeJsonKeyValue("antivirus", c->children[0]->text) + makeJsonKeyValue("detection", "File not detected")
                               + makeJsonKeyValue("date",c->children[2]->text)) << "," <<  endl;
            }
            else
            {
                ss << makeJson(makeJsonKeyValue("antivirus", c->children[0]->text) + makeJsonKeyValue("detection", c->children[1]->text)
                               + makeJsonKeyValue("date",c->children[2]->text)) << "," << endl;
            }

        }
        result = makeJsonKeyValue("antivir_list", makeJsonList(ss.str()), true);
    }

    return result;
}

std::string ResultsAnalyzer::getSHA()
{
    auto basicInfo = findElement("id", "basic-info");
    stringstream ss;

    if (basicInfo)
    {
        basicInfo = basicInfo->children[0]->children[0]->children[0]->children[0];
        // SHA
        ss << makeJsonKeyValue(basicInfo->children[0]->children[0]->text, basicInfo->children[0]->children[1]->text);
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
        ss << makeJsonKeyValue(basicInfo->children[1]->children[0]->text, basicInfo->children[1]->children[1]->text);

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
        ss << makeJsonKeyValue(basicInfo->children[2]->children[0]->text, basicInfo->children[2]->children[1]->text);
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
        ss << makeJsonKeyValue(basicInfo->children[3]->children[0]->text, basicInfo->children[3]->children[1]->text);
    }

    return ss.str();
}

std::string ResultsAnalyzer::getFileDetails()
{
    auto fileDetails = findElement("id", "file-details");
    stringstream ss;
    string result;

    if (fileDetails)
    {
        //szukamy miejsca w którym znajduja sie szczegoly
        bool found = false;
        for(int i = 0; i < fileDetails->children.size(); ++i)
        {
            if(fileDetails->children[i]->text.find("File identification") != string::npos)
            {
                fileDetails = fileDetails->children[i+1];
                found = true;
                break;
            }
        }

        // jeśli nie znalezlismy to zwracamy pusty string
        if(!found)
            return "";

        for (auto& c : fileDetails->children)
        {
            auto key = findElement("class", "field-key", c);
            auto value = findElement("class", "field-value", c);
            if(key)
                ss << makeJsonKeyValue(key->text, value ? value->text : c->text);
        }
        result = makeJsonKeyValue("file_details", makeJson(ss.str()), true);

    }

    return result;
}

std::string ResultsAnalyzer::getMetadata()
{
    auto fileDetails = findElement("id", "file-details");
    stringstream ss;
    string result;

    if (fileDetails)
    {
        //szukamy miejsca w którym znajduje się metadata
        bool found = false;
        for(int i = 0; i < fileDetails->children.size(); ++i)
        {
            if(fileDetails->children[i]->text.find("metadata") != string::npos)
            {
                fileDetails = fileDetails->children[i+1];
                found = true;
                break;
            }
        }

        // jeśli nie znalezlismy to zwracamy pusty string
        if(!found)
            return "";

        for (auto& c : fileDetails->children)
        {
            auto key = findElement("class", "field-key", c);
            auto value = findElement("class", "field-value", c);
            ss << makeJsonKeyValue(key->text, value ? value->text : c->text);
        }

        result = makeJsonKeyValue("metadata", makeJson(ss.str()), true);

    }

    return result;
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

std::string ResultsAnalyzer::getKeyName(const std::string &key)
{
    return "\"" + replaceSpaces(trimWhitespaces(key.substr(0, key.find_first_of(":")))) + "\"";
}

std::string ResultsAnalyzer::getValueName(const std::string &val)
{
    return "\"" + trimWhitespaces(val) + "\"";
}

std::string ResultsAnalyzer::makeJsonKeyValue(const std::string &key, const std::string &val, bool isValueJson)
{
    if(isValueJson)
        return getKeyName(key) + ":" + val;

    return getKeyName(key) + ":" + getValueName(val) + ",";
}

std::string ResultsAnalyzer::makeJson(const std::string& str)
{
    std::string temp = trimWhitespaces(str);
    if(temp.find_last_of(",") == temp.size()-1)
        temp.pop_back();
    return "{\n" + temp + "\n}";
}

string ResultsAnalyzer::makeJsonList(const string& str)
{
    string temp = trimWhitespaces(str);

    if(temp.find_last_of(",") == temp.size()-1)
        temp.pop_back();

    return "[\n" + temp + "\n]";
}


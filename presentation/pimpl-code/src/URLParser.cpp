// URLParser.cpp
// By: Matt McCarthy
#ifndef URLPARSER_CPP
#define URLPARSER_CPP

#include <string>
#include <vector>
#include <sstream>
#include <regex.h>

#include "../URLParser.h"

using std::string;
using std::vector;
using std::stringstream;

const static string URLFORMAT_REGEX = "^([^/:]+:)?//([^:/]{1,99})(:[0-9]{1,5})?(.{0,200})$";

NetLib::URLParser::URLParser(string InputURL, vector<string> AllowableProtocols, vector<int> DefaultPorts)
    throw (BadInput, BadProtocol) : mHostAddress(""), mPath(""), mProtocol(""), mPort(0)
    
{
    regex_t vURLExpression;

    // Compile the regular expression
    regcomp(&vURLExpression, URLFORMAT_REGEX.c_str(), REG_EXTENDED | REG_ICASE);
//    if (regcomp(&vURLExpression, URLFORMAT_REGEX.c_str(), REG_EXTENDED | REG_ICASE))
//    {
//        std::cerr << "bad regex\n";
//        std::cin.ignore();
//    }

    string vURL = InputURL;
    regmatch_t vExpressionMatches[5];

    // Compare the URL against the regular expression
    if (regexec(&vURLExpression, vURL.c_str(), 5, vExpressionMatches, 0))
        throw BadInput(InputURL);

    int vProtocolIndex = 0;

    // Verify protocol
    if (vExpressionMatches[1].rm_so != -1)
    {
        string vProtocolUsed = vURL.substr(vExpressionMatches[1].rm_so,
                                           vExpressionMatches[1].rm_eo - vExpressionMatches[1].rm_so);

        for (unsigned fCount = 0; fCount < vProtocolUsed.length(); fCount++)
            vProtocolUsed[fCount] = tolower(vProtocolUsed[fCount]);

        bool vFlag = false;

        for (int vCount = 0; vCount < AllowableProtocols.size(); vCount++)
            if (vProtocolUsed == AllowableProtocols[vCount])
            {
                vFlag = true;
                vProtocolIndex = vCount;
            }

        if (!vFlag)
            throw BadProtocol(vProtocolUsed);

        mProtocol = vProtocolUsed;
    }

    // Extract host
    string vHost = "";

	vHost = vURL.substr(vExpressionMatches[2].rm_so,
                        vExpressionMatches[2].rm_eo - vExpressionMatches[2].rm_so);

    mHostAddress = vHost;

    // Extract port
    int vPort = DefaultPorts[vProtocolIndex];
    if (vExpressionMatches[3].rm_so != -1)
	{
		stringstream vPortConvert;

		vPortConvert << vURL.substr(vExpressionMatches[3].rm_so + 1,
                                    vExpressionMatches[3].rm_eo - vExpressionMatches[3].rm_so - 1);

		vPort = 0;
		vPortConvert >> vPort;
	}

	mPort = vPort;

	// Extract path
	string vPath = "";

	vPath = vURL.substr(vExpressionMatches[4].rm_so,
                        vExpressionMatches[4].rm_eo - vExpressionMatches[4].rm_so);

    if (vPath == "")
        vPath = "/";

    mPath = vPath;
}

NetLib::URLParser::~URLParser() {}

string NetLib::URLParser::GetHostAddress()
{
    return mHostAddress;
}

string NetLib::URLParser::GetPath()
{
    return mPath;
}

string NetLib::URLParser::GetProtocol()
{
    return mProtocol;
}

int NetLib::URLParser::GetPort()
{
    return mPort;
}

#endif

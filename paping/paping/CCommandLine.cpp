/*
Copyright (c) 2010 Mike Lovell

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include "stdafx.h"


using namespace std;


void CCommandLine::PrintUsage()
{
	wcout << L"paping v1.0.0 - http://en.wikipedia.org/wiki/MIT_License"				<< endl << endl;
	wcout << L"Syntax: paping [options] destination"									<< endl << endl;
	wcout << L"Options:"																<< endl << endl;
	wcout << L" -?, --help\tdisplay usage"												<< endl;
	wcout << L" -p, --port N\tset TCP/UDP port N"										<< endl;
	wcout << L"     --tcp\tuse TCP protocol (default)"									<< endl;
	wcout << L"     --udp\tuse UDP protocol"											<< endl;
	wcout << L" -t, --timeout\ttimeout in milliseconds (default 1000)"					<< endl;
	wcout << L" -c, --count N\tset number of checks to N"								<< endl;
}


int CCommandLine::ProcessArguments(int argc, pwstr argv[], CSettings &settings)
{
	int			value			= 0;
	int			match			= 0;
	bool		gotDestination	= false;
	
	settings	= CSettings();

	for (int i=1; i<argc; i++)
	{
		bool	matchAny	=	false;
		
		if ((match = CCommandLine::matchArgument(i, argc, argv, L"-?", L"--help", false, value)) == MATCH_YES)
		{
			return 1;
		}

		if ((match = CCommandLine::matchArgument(i, argc, argv, L"-p", L"--port", true, value)) == MATCH_YES)
		{
			i++;
			settings.port	= value;
			matchAny		= true;
			continue;
		}

		if ((match = CCommandLine::matchArgument(i, argc, argv, L"-c", L"--count", true, value)) == MATCH_YES)
		{
			i++;
			settings.count		= value;
			settings.continous	= false;
			matchAny			= true;
			continue;
		}

		if ((match = CCommandLine::matchArgument(i, argc, argv, L"-t", L"--timeout", true, value)) == MATCH_YES)
		{
			i++;
			settings.timeoutms = 0;
			matchAny	= true;
			continue;
		}

		if ((match = CCommandLine::matchArgument(i, argc, argv, NULL, L"--tcp", false, value)) == MATCH_YES)
		{
			settings.type = IPPROTO_TCP;
			continue;
		}

		if ((match = CCommandLine::matchArgument(i, argc, argv, NULL, L"--udp", false, value)) == MATCH_YES)
		{
			settings.type = IPPROTO_UDP;
			continue;
		}

		if (match == MATCH_INVALIDVALUE) return 1;
		if (!matchAny && gotDestination) return 1;

		gotDestination = true;

		settings.hostname = CStringManipulation::WideToANSI(argv[i]);
	}

	if (settings.port <= 0) return 1;

	return 0;
}


int CCommandLine::matchArgument(int pos, int total, pwstr argv[], pcwstr shortName, pcwstr longName, bool expectValue, int &value)
{
	if ((shortName != NULL && !std::wcscmp(argv[pos], shortName)) || (longName != NULL && !std::wcscmp(argv[pos], longName)))
	{
		if (expectValue)
		{
			if (pos + 1 == total) return MATCH_INVALIDVALUE;
		
			value = _ttoi(argv[pos+1]);

			if (value <=0) return MATCH_INVALIDVALUE;
		}

		return MATCH_YES;
	}

	return MATCH_NO;
}


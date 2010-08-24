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

CSettings	settings;
bool		exiting	= false;


BOOL WINAPI ConsoleHandler(DWORD CEvent)
{
	switch(CEvent)
	{
		case CTRL_BREAK_EVENT:
			settings.PrintStatistics();
			wcout << endl;
			break;
		default:
			WSACleanup();
			settings.PrintStatistics();
			exiting = true;
			exit(1);
			break;
	}

	return TRUE;
}



int _tmain(int argc, _TCHAR* argv[])
{
	int	result	= 0;
	
	wcout << endl;

	if (argc <= 2)
	{
		CCommandLine::PrintUsage();
		return 1;
	}

	if (result = CCommandLine::ProcessArguments(argc, argv, settings) != 0)
	{
		CCommandLine::PrintUsage();
		return result;
	}
	
	if (SetConsoleCtrlHandler((PHANDLER_ROUTINE)ConsoleHandler, true) == false)
	{
		std::wcerr << "Cannot set control handler" << endl;
		return 1;
	}


	if (result = settings.host.Resolve(settings.hostname) != 0)
	{
		wcerr << L"Unable to resolve '" << settings.hostname << "' (ERR: " << result << ")";

		return result;
	}
	
	settings.host.PrintConnectingLine(settings.port, settings.type);

	uint32	i = 0;
	
	CTimer	timer = CTimer();

	while (settings.continous || i < settings.count)
	{		
		timer.Start();
		int result		= CConnection::CheckConnection(settings);
		timer.Stop();
		
		uint32	elapsed	= timer.GetElapsed();

		if (exiting) return 0;

		if (result == CONNECT_SUCCESS)
		{
			settings.statistics.NewData(elapsed);

			wcout << "Connected to " << inet_ntoa(settings.host.GetIPAddress()) << ": time=" << elapsed << "ms protocol=" << CType::GetProtocolName(settings.type) << " port=" << settings.port << endl;
		}

		if (result == CONNECT_TIMEOUT)
		{
			settings.statistics.NewData();
			wcout << "Connect timed out." << endl;
		}

		if (result == CONNECT_FAILURE)
		{
			settings.statistics.NewData();
			wcout << "General Failure." << endl;
		}

		i++;

		if (settings.continous || i < settings.count)
		{
			if ((result == CONNECT_SUCCESS || result == CONNECT_FAILURE) && elapsed < 1000)
			{
				Sleep(1000 - elapsed);
			}
		}
	}

	WSACleanup();
	settings.PrintStatistics();

	return 0;
}


#include "standard.h"


using namespace std;


void arguments_c::PrintBanner()
{
	cout << "paping v" << VERSION << " - Copyright (c) " << YEAR << " " << AUTHOR << endl << endl;
}


void arguments_c::PrintUsage()
{
	cout << i18n_c::GetString(STRING_USAGE) << endl;
}


int	arguments_c::Process(int argc, pc_t argv[], arguments_c &arguments)
{
	int		result			= 0;
	int		value			= 0;
	bool	anyMatch		= false;
	bool	gotDestination	= false;

	arguments.Port		= 0;
	arguments.Count		= 0;
	arguments.Timeout	= 1000;
	arguments.Type		= IPPROTO_TCP;
	arguments.Continous	= true;
	arguments.UseColor	= true;

	for (int i=1; i<argc; i++)
	{
		anyMatch	= false;

		if (result = arguments_c::match(i, argc, argv, "-p", "--port", true, arguments.Port, anyMatch) != SUCCESS) return result;
		if (result = arguments_c::match(i, argc, argv, "-c", "--count", true, arguments.Count, anyMatch) != SUCCESS) return result;
		if (result = arguments_c::match(i, argc, argv, "-t", "--timeout", true, arguments.Timeout, anyMatch) != SUCCESS) return result;

		if (anyMatch)
		{
			i++;
			continue;
		}

		if (result = arguments_c::match(i, argc, argv, NULL, "--nocolor", false, value, anyMatch) != SUCCESS) return result;
		if (value == 1) arguments.UseColor = false;


		if (!anyMatch)
		{
			if (!gotDestination)
			{
				gotDestination			= true;
				arguments.Destination	= argv[i];
			}
			else
			{
				return ERROR_INVALIDARGUMENTS;
			}
		}
	}

	if (arguments.Count <= 0)
	{
		arguments.Count		= -1;
		arguments.Continous = true;
	}
	else
	{
		arguments.Continous = false;
	}

	if (arguments.Port <= 0) return ERROR_INVALIDARGUMENTS;
	if (arguments.Timeout <= 0) return ERROR_INVALIDARGUMENTS;
	if (!gotDestination) return ERROR_INVALIDARGUMENTS;

	return SUCCESS;
}


int	arguments_c::match(int pos, int total, pc_t argv[], pcc_t shortName, pcc_t longName, bool expectedValue, int &value, bool &anyMatch)
{
	if	(
				(	shortName != NULL						&&
					strlen(shortName) == strlen(argv[pos])	&&
					!strcmp(shortName, argv[pos]))
			||	(	longName != NULL						&&
					strlen(longName) == strlen(argv[pos])	&&
					!strcmp(longName, argv[pos]))
		)
		{
			anyMatch = true;

			if (expectedValue)
			{
				if (pos+1 == total) return ERROR_INVALIDARGUMENTS;
				value	= atoi(argv[pos+1]);
			}
			else
			{
				value = 1;
			}

			return SUCCESS;
		}

	if (!expectedValue) value = 0;

	return SUCCESS;
}

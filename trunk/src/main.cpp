#include "standard.h"

using namespace std;


void printError(int error);
int printConnectInfo(host_c host);
int printSuccessfulConnection(host_c host, double time);
int printFailedConnection(int failtype);
int printStats();

void signalHandler(int id);


bool	useColor	= false;
int		exitCode	= 0;
stats_c	stats;



int main(int argc, pc_t argv[])
{
	host_c		host;
	int			result;
	arguments_c	arguments;


	stats.Attempts	= 0;
	stats.Connects	= 0;
	stats.Failures	= 0;
	stats.Minimum	= 0.0;
	stats.Maximum	= 0.0;
	stats.Total		= 0.0;

	arguments_c::PrintBanner();

	result = arguments_c::Process(argc, argv, arguments);

	if (result != SUCCESS)
	{
		arguments_c::PrintUsage();
		return ERROR_INVALIDARGUMENTS;
	}

	useColor = arguments.UseColor;

	result = socket_c::Resolve(arguments.Destination, host);

	if (result == SUCCESS)
	{
		socket_c::SetPortAndType(arguments.Port, arguments.Type, host);

		if (result != SUCCESS)
		{
			printError(result);
			return result;
		}

		result = printConnectInfo(host);

		if (result != SUCCESS)
		{
			printError(result);
			return result;
		}
	}
	else
	{
		printError(result);
		return result;
	}

	signal(SIGINT, &signalHandler);


	unsigned int	i		= 0;

	double			time	= 0.0;

	while (arguments.Continous || i < (unsigned int)arguments.Count)
	{
		result = socket_c::Connect(host, arguments.Timeout, time);

		stats.Attempts++;

		if (result == SUCCESS)
		{
			stats.Connects++;
			stats.Total += time;
			stats.UpdateMaxMin(time);

			printSuccessfulConnection(host, time);
		}
		else
		{
			exitCode = 1;
			stats.Failures++;

			printFailedConnection(result);
		}

		#ifdef WIN32	// Windows cannot sleep to that accuracy (I think!)
			if ((int)time < 1000) Sleep((1000 - (int)time));
		#else
			if ((int)time < 1000) usleep((1000 - (int)time) * 1000);
		#endif

		i++;
	}


	printStats();	

	return exitCode;
}


void signalHandler(int id)
{
	switch (id)
	{
		case SIGINT:
			printStats();
			exit(exitCode);
			return;
	}
}


void printError(int error)
{
	if (useColor)
		print_c::FormattedPrint(PRINT_COLOR_RED, i18n_c::GetString(error));
	else
		print_c::FormattedPrint(NULL, i18n_c::GetString(error));

	cout << endl;
}


int printConnectInfo(host_c host)
{
	int		length	= 0;

	length = host.GetConnectInfoString(NULL);

	pc_t	info	= new (nothrow) char[length + 1];

	if (info == 0)
	{
		info = NULL;
		return ERROR_POUTOFMEMORY;
	}

	host.GetConnectInfoString(info);

	if (useColor)
		print_c::FormattedPrint(PRINT_COLOR_YELLOW, info);
	else
		print_c::FormattedPrint(NULL, info);

	cout << endl << endl;

	delete[] info;

	return SUCCESS;
}


int printSuccessfulConnection(host_c host, double time)
{
	int		length	= 0;

	length = host.GetSuccessfulConnectionString(NULL, time);

	pc_t	data	= new (nothrow) char[length + 1];

	if (data == 0)
	{
		data = NULL;
		return ERROR_POUTOFMEMORY;
	}

	host.GetSuccessfulConnectionString(data, time);

	if (useColor)
		print_c::FormattedPrint(PRINT_COLOR_GREEN, data);
	else
		print_c::FormattedPrint(NULL, data);

	cout << endl;

	delete[] data;

	return SUCCESS;
}


int printStats()
{
	int	length = 0;

	length = stats.GetStatisticsString(NULL);

	pc_t	str	= new (nothrow) char[length + 1];

	if (str == 0)
	{
		str = NULL;
		return ERROR_POUTOFMEMORY;
	}

	stats.GetStatisticsString(str);

	if (useColor)
		print_c::FormattedPrint(PRINT_COLOR_BLUE, str);
	else
		print_c::FormattedPrint(NULL, str);

	cout << endl;

	delete[] str;

	return SUCCESS;
}


int printFailedConnection(int error)
{
	if (useColor)
		print_c::FormattedPrint(PRINT_COLOR_RED, i18n_c::GetString(error));
	else
		print_c::FormattedPrint(NULL, i18n_c::GetString(error));

	cout << endl;

	return SUCCESS;
}

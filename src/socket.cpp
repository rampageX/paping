#include "standard.h"

using namespace std;

int socket_c::Resolve(pcc_t hostname, host_c &host)
{
	hostent*	remoteHost	= NULL;

	#ifdef WIN32	// Init Winsock in Windows
		WSADATA	wsaData;
		if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) return ERROR_SOCKET_GENERALFAILURE;
	#endif

	remoteHost = gethostbyname(hostname);

	#ifdef WIN32	// Cleanup Winsock in Windows
		WSACleanup();
	#endif

	if (remoteHost == NULL) return ERROR_SOCKET_CANNOTRESOLVE;

	host.IPAddress	= *(in_addr*)remoteHost->h_addr_list[0];
	host.Hostname	= remoteHost->h_name;

	host.HostIsIP = !strcmp(hostname, host.Hostname);

	return SUCCESS;
}


int socket_c::SetPortAndType(int port, int type, host_c &host)
{
	host.Port	= port;
	host.Type	= type;

	return SUCCESS;
}


pcc_t socket_c::GetFriendlyTypeName(int type)
{
	switch (type)
	{
		case IPPROTO_TCP:
			return "TCP";
		case IPPROTO_UDP:
			return "UDP";
		default:
			return "UNKNOWN";
	}
}


int socket_c::GetSocketType(int type)
{
	switch (type)
	{
		case IPPROTO_UDP:
			return SOCK_DGRAM;
		default:
			return SOCK_STREAM;
	}
}


int socket_c::Connect(host_c host, int timeout, double &time)
{
	int		result	= 0;
	int		clientSocket;


	#ifdef WIN32	// Init Winsock in Windows
		WSADATA	wsaData;
		if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) return ERROR_SOCKET_GENERALFAILURE;
	#endif

	clientSocket = socket(AF_INET, socket_c::GetSocketType(host.Type), host.Type);

	if (clientSocket == -1) return ERROR_SOCKET_GENERALFAILURE;

	sockaddr_in	clientAddress;

	clientAddress.sin_addr		= host.IPAddress;
	clientAddress.sin_family	= AF_INET;
	clientAddress.sin_port		= htons(host.Port);

	timeval	tv;
	
	// No blocking for Windows/Linux
	#ifdef WIN32
		ULONG	mode = 1;
		ioctlsocket(clientSocket, FIONBIO, &mode);
	#else
		long arg = fcntl(clientSocket, F_GETFL, host.Type);
		arg = fcntl(clientSocket, F_SETFL, arg | O_NONBLOCK);
	#endif


	tv.tv_sec 	= 0;
	tv.tv_usec	= timeout * 1000;

	timer_c	timer;

	timer.Start();		

	connect(clientSocket, (sockaddr*)&clientAddress, sizeof(clientAddress));

	fd_set	read, write;

	FD_ZERO(&read);
	FD_ZERO(&write);

	FD_SET(clientSocket, &read);
	FD_SET(clientSocket, &write);
	
	result = select(clientSocket + 1, &read, &write, NULL, &tv);
	
	if (result != 1)
	{
		close(clientSocket);

		#ifdef WIN32	// Cleanup Winsock in Windows
			WSACleanup();
		#endif

		return ERROR_SOCKET_TIMEOUT;
	}

	time		= timer.Stop();

	if (!FD_ISSET(clientSocket, &read) && !FD_ISSET(clientSocket, &write))
	{
		close(clientSocket);

		#ifdef WIN32	// Cleanup Winsock in Windows
			WSACleanup();
		#endif

		return ERROR_SOCKET_TIMEOUT;
	}

	close(clientSocket);

	#ifdef WIN32	// Cleanup Winsock in Windows
		WSACleanup();
	#endif

	return SUCCESS;
}

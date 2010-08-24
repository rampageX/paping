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


int CConnection::CheckConnection(CSettings settings)
{
	SOCKET	clientSocket;
	WSADATA	wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) return CONNECT_FAILURE;

	clientSocket = socket(AF_INET, CConnection::ProtocolToSocketType(settings.type), settings.type);
	
	if (clientSocket == INVALID_SOCKET)
	{
		WSACleanup();
		return CONNECT_FAILURE;
	}

	ULONG	mode = 1;	// Non-blocking

	ioctlsocket(clientSocket, FIONBIO, &mode);

	sockaddr_in	clientAddress;

	clientAddress.sin_addr		= settings.host.GetIPAddress();
	clientAddress.sin_family	= AF_INET;
	clientAddress.sin_port		= htons(settings.port);
	
	int					result;

	connect(clientSocket, (SOCKADDR*)&clientAddress, sizeof(clientAddress));

	if (result = WSAGetLastError() == WSAEWOULDBLOCK)
	{	// Waiting
		fd_set	write, error;
		TIMEVAL	timeout;

		FD_ZERO(&write);
		FD_ZERO(&error);
		FD_SET(clientSocket, &write);
		FD_SET(clientSocket, &error);

		timeout.tv_sec = 0;
		timeout.tv_usec = settings.timeoutms * 1000;

		result = select(0, NULL, &write, &error, &timeout);
		
		WSACleanup();

		if (result == 0) return CONNECT_TIMEOUT;
		if (FD_ISSET(clientSocket, &write)) return CONNECT_SUCCESS;

		return CONNECT_FAILURE;
	}
	else
	{	// Immediate Connection
		WSACleanup();

		return CONNECT_SUCCESS;
	}
}


int CConnection::ProtocolToSocketType(int type)
{
	switch (type)
	{
		case IPPROTO_TCP:
			return SOCK_STREAM;
		default:
			return SOCK_DGRAM;
	}
}
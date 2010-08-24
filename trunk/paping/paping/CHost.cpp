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


int CHost::Resolve(PCSTR hostname)
{
	WSADATA	wsaData;
	hostent*	remoteHost;
	int			result;

	if (result = WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) return result;

	remoteHost = gethostbyname(hostname);

	if (remoteHost == NULL) return WSAGetLastError();
	
	WSACleanup();

	this->ipAddress_.s_addr	= *(u_long*)remoteHost->h_addr_list[0];
	this->requestedName_	= hostname;
	this->officialName_		= remoteHost->h_name;
	this->hasResolved_		= true;

	return 0;
}


pcstr CHost::GetOfficialName()
{
	return this->officialName_;
}


in_addr CHost::GetIPAddress()
{
	return this->ipAddress_;
}


void CHost::PrintConnectingLine(uint32 port, int type)
{

	if (!strcmp(this->officialName_, this->requestedName_))
	{
		wcout << L"Connecting to " << inet_ntoa(this->ipAddress_) << L" on ";
	}
	else
	{
		wcout << L"Connecting to " << this->officialName_ << L" [" << inet_ntoa(this->ipAddress_) << L"] on ";
	}

	wcout << port << L"/" << CType::GetProtocolName(type) << L":" << endl;
}
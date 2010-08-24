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

#pragma once
#define WIN32_LEAN_AND_MEAN

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <signal.h>


// TODO: reference additional headers your program requires here
#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#pragma comment(lib, "ws2_32.lib")

//Types
typedef unsigned	_int64		uint64;
typedef unsigned	_int32		uint32;
typedef	const		wchar_t*	pcwstr;
typedef	const		char*		pcstr;
typedef				wchar_t*	pwstr;
typedef				char*		pstr;
typedef	unsigned	short		ushort;

//Defines
#define	MATCH_NO			0
#define	MATCH_YES			1
#define	MATCH_INVALIDVALUE	2


#define	CONNECT_SUCCESS		0
#define	CONNECT_TIMEOUT		1
#define	CONNECT_FAILURE		2


// Custom
#include "CStringManipulation.h"
#include "CTimer.h"
#include "CType.h"
#include "CHost.h"
#include "CLatency.h"
#include "CStatistics.h"
#include "CSettings.h"
#include "CCommandLine.h"
#include "CConnection.h"
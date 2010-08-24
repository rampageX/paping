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


CStatistics::CStatistics()
{
	this->latency_		= CLatency();
	this->total_		= 0;
	this->failed_		= 0;
	this->succeeded_	= 0;
}


void CStatistics::NewData()
{
	this->total_++;
	this->failed_++;
}


void CStatistics::NewData(uint32 latency)
{
	this->total_++;
	this->succeeded_++;

	this->latency_.NewData(latency);
}


CLatency CStatistics::GetLatency()
{
	return this->latency_;
}


uint32 CStatistics::GetTotal()
{
	return this->total_;
}


uint32 CStatistics::GetSucceeded()
{
	return this->succeeded_;
}


uint32 CStatistics::GetFailed()
{
	return this->failed_;
}


double CStatistics::GetFailedPercentage()
{
	if (this->total_ > 0)
	{
		return ((double)this->failed_ / (double)this->total_) * 100;
	}

	return 0.00f;
}


void CStatistics::Print(PCSTR ipAddress, int type, uint32 port)
{
		wcout << L"\nConnection statistics for " << ipAddress << L" " << port << "/" << CType::GetProtocolName(type) << L":" << endl;
		wcout << L"\tConnections: Total = " << this->total_ << L", Succeeded = " << this->succeeded_ << L", Failed = " << this->failed_ << L" (" << this->GetFailedPercentage() << L"% failure)" << endl;
		wcout << L"Approximate connection times in milli-seconds:" << endl;
		wcout << L"\tMinimum = " << this->latency_.GetMinimum() << L"ms, Maximum = " <<  this->latency_.GetMaximum() << L"ms, Average = " << this->latency_.GetAverage() << L"ms" << endl;
}
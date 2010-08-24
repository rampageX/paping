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


CLatency::CLatency()
{
	this->anyData_	= false;
	this->minimum_	= 0;
	this->maximum_	= 0;
	this->total_	= 0;
	this->count_	= 0;
}


void CLatency::NewData(uint32 value)
{
	if (!this->anyData_)
	{
		this->minimum_	= value;
		this->maximum_	= value;
		
		this->anyData_	= true;
	}
	else
	{
		this->checkMinimumMaximum(value);
	}

	this->total_	+=value;
	this->count_	++;
}


uint32 CLatency::GetMinimum()
{
	return this->minimum_;
}


uint32 CLatency::GetMaximum()
{
	return this->maximum_;
}


uint32 CLatency::GetAverage()
{
	if (this->count_ > 0)
	{
		return (uint32)this->total_ / this->count_;
	}

	return 0;
}


void CLatency::checkMinimumMaximum(uint32 value)
{
	if (value < this->minimum_) this->minimum_ = value;
	if (value > this->maximum_) this->maximum_ = value;
}


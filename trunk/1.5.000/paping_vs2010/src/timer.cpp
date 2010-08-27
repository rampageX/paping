#include "standard.h"

using namespace std;


void timer_c::Start()
{
	this->hasValue_ = true;

	gettimeofday(&this->start_, NULL);
}


double timer_c::Stop()
{
	if (!this->hasValue_) return 0;

	gettimeofday(&this->stop_, NULL);

	double	usecStop	= this->stop_.tv_usec + (this->stop_.tv_sec * 1000000);
	double	usecStart	= this->start_.tv_usec + (this->start_.tv_sec * 1000000);

	return (usecStop - usecStart) /  1000;
}

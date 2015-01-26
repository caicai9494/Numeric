#include "Timer.h"


void Timer::start_timer()
{
    if(!init_time)
	init_time = clock();
    else
	cout << "Previous timer is still running.\n";
}
void Timer::end_timer()
{
    if(!init_time)
	cout << "Timer hasn't started.\n";
    else
	cout << "Elapsed "<< (float)(clock() - init_time) / CLOCKS_PER_SEC << " s\n";
	init_time = 0;
}

Timer& Timer::operator= (const Timer& tm){return *this;}
clock_t Timer::init_time = 0;

#ifndef _TIMER_H
#define _TIMER_H

#include <iostream>
#include <ctime>
using namespace std;

class Timer
{
    public:
	static void start_timer();
	static void end_timer();
    private:
	Timer() {}
	Timer(const Timer& tm) {}
	Timer& operator= (const Timer& tm);
	static clock_t init_time;
};

#endif

#ifndef __UTIL_H
#define __UTIL_H
#include <ctime>
#include <iostream>

using namespace std;

static clock_t start_time = 0;

template <typename T>
int sign(T val)
{
    return (T(0) < val) - (val - T(0));
}

namespace util
{

    template<typename T>
    T abs(T val)
    {
	return val > 0 ? val : -val;
    }	
}

void start_timer();
void end_timer();
#endif

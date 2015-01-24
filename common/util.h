#ifndef __UTIL_H
#define __UTIL_H
#include <ctime>
#include <iostream>

using namespace std;

static clock_t start_time = 0;


namespace util
{

    template <typename T>
    int sign(T val)
    {
	return (val > 0) ? 1 : (val == 0) ? 0 : -1;
    }

    template<typename T>
    T abs(T val)
    {
	return val > 0 ? val : -val;
    }	

    template<typename T>
    void swap(T &val1, T &val2)
    {
	T temp;
	temp = val1;
	val1 = val2;
	val2 = temp;
    }

}

void start_timer();
void end_timer();
#endif

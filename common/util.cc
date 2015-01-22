#include "util.h"

void start_timer()
{
    if(!start_time)
	start_time = clock();
    else
	cout << "Previous timer is still running.\n";
}

void end_timer()
{
    if(!start_time)
	cout << "Timer hasn't started.\n";
    else
	cout << "Elapsed "<< (float)(clock() - start_time) / CLOCKS_PER_SEC << " s\n";
	start_time = 0;

}

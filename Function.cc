#include "Function.h"

Function::~Function(){}

double Function::invokeFunction(double *para, unsigned int N)const {}


Function1v::Function1v()
{
    funcPtr = NULL;
}
Function1v::~Function1v()
{
    funcPtr = NULL;
}
void Function1v::setFuncPtr(FuncPtr fPtr)
{
    if(&funcPtr != NULL)
	funcPtr = fPtr;
}

double Function1v::invokeFunction(double *para, unsigned int N) const
{
    assert(funcPtr != NULL);

    try
    {
	return (*funcPtr)(para, N);
    }
    catch(std::overflow_error &e)
    {
	std::cout << "standard exception :" << e.what(); 
    }
}

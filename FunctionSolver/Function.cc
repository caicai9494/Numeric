#include "Function.h"

Function::~Function(){}

double Function::invokeFunction(double *para, unsigned int N)const {return 0;}

void Function::setFunctionString(string s)
{
    functionString = s;
}
string Function::toString()
{
    return functionString;
}

Function1v::Function1v()
{
    funcPtr = NULL;
}
Function1v::~Function1v()
{
    funcPtr = NULL;
}
Function1v& Function1v::operator= (const Function1v&)
{
    return *this;
}
void Function1v::setFuncPtr(FuncPtr fPtr)
{
    if(&funcPtr != NULL)
	funcPtr = fPtr;
}

double Function1v::invokeFunction(double *para, unsigned int N) const
{
    assert(funcPtr != NULL);

    return (*funcPtr)(para, N);
}

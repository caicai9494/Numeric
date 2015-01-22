#ifndef _FUNCTION_H
#define _FUNCTION_H
#include <iostream>
#include <cassert>
#include <stdexcept>


class Function
{
    public:
	virtual ~Function() = 0;
	virtual double invokeFunction(double *para, unsigned int N) const;
};

class Function1v: public Function
{
    typedef double (*FuncPtr) (double *para, unsigned int N) ;
    public:
	Function1v();
	~Function1v(); 
	void setFuncPtr(FuncPtr fPtr);
	virtual double invokeFunction(double *para, unsigned int N = 1) const;
    private:
	//check denominator and throw overflow_error if it is zero
	FuncPtr funcPtr;
	Function1v& operator= (const Function1v&) {}
	Function1v(const Function1v &) {}
};
#endif

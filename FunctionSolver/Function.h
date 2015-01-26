#ifndef _FUNCTION_H
#define _FUNCTION_H
#include <iostream>
#include <cassert>
#include <stdexcept>
#include <string>

using namespace std;


class Function
{
    public:
	virtual ~Function() = 0;
	virtual double invokeFunction(double *para, unsigned int N) const;
	void setFunctionString(string s);
	string toString();
    private:
	string functionString;
};

class Function1v: public Function
{
    typedef double (*FuncPtr) (double *para, unsigned int N) ;
    public:
	Function1v();
	~Function1v(); 
	void setFuncPtr(FuncPtr fPtr);
	//throw overflow_error if divide by zero
	virtual double invokeFunction(double *para, unsigned int N = 1) const;
    private:
	//check denominator and throw overflow_error if it is zero
	FuncPtr funcPtr;
	Function1v& operator= (const Function1v&) ;
	Function1v(const Function1v&) {}
};
#endif

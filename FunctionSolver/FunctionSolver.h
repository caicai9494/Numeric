#ifndef _FUNCTIONSOLVER_H
#define _FUNCTIONSOLVER_H 
#include "Function.h"
#include "../common/util.h"
#include <cstdlib>

using namespace std;

class FunctionSolver
{
    public:
	FunctionSolver();
	virtual ~FunctionSolver() = 0;
	void setIteration(unsigned int itr);
	void setIgnorance(double ign);
	void setBound(double lb, double ub, bool ilb = true, bool iub = true);
	void setFunction(Function *f);

	virtual bool isSetUp();


    protected:
	double lowerBound;
	double upperBound;
	bool isLowerBoundIncluded;
	bool isUpperBoundIncluded;
	unsigned int iteration;
	double ignorance;

	//clean func yourself
	Function *func;

	double evaluateFunction(double para);

    private:
	bool isIterationSet;
	bool isIgnoranceSet;
	bool isBoundSet;
	bool isFunctionSet;

};

class BisectionFunctionSolver: public FunctionSolver
{
    public:
        BisectionFunctionSolver();  
	~BisectionFunctionSolver();

	//If no solution in the boundry
	//Return a value bigger than upperBound
	double BisectionMethod(bool isSilent = true);
};

class NewtonFunctionSolver: public FunctionSolver
{
    public:
	NewtonFunctionSolver();
	~NewtonFunctionSolver();
	double NewtonMethod(double ini_x, bool isSilent = true);
	void setFirstPrime(Function *func);
	bool isSetUp();

    private:
	Function *first_prime;
	//throw overflow_error when divide by zero
	double evaluateFirstPrime(double val);
};

class SecantFunctionSolver: public FunctionSolver
{
    public:
	SecantFunctionSolver();
	~SecantFunctionSolver();

	//throw overflow_error when divide by zero
	double SecandMethod(bool isSilent = true);
};

#endif

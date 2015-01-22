#include "FunctionSolver.h"
#include "Function.h"

FunctionSolver::FunctionSolver()
{
    func = NULL;
    isFunctionSet = isIterationSet = isBoundSet = isIgnoranceSet = false;
}

FunctionSolver::~FunctionSolver()
{
    //func = NULL;
}

void FunctionSolver::setIteration(unsigned int itr)
{
    iteration = itr;
    isIterationSet = true;
}
void FunctionSolver::setIgnorance(double ign)
{
    ignorance = ign;
    isIgnoranceSet = true;
}

void FunctionSolver::setBound(double lb, double ub, bool ilb, bool iub)
{
    assert(lb <= ub);
    lowerBound = lb;
    upperBound = ub;
    isLowerBoundIncluded = ilb;
    isUpperBoundIncluded = iub;

    isBoundSet = true;
}
void FunctionSolver::setFunction(Function *f)
{
    if(f != NULL)
	func = f;
    isFunctionSet = true;
}

bool FunctionSolver::isSetUp()
{
    return isIterationSet && isIgnoranceSet && isBoundSet && isFunctionSet;
}

double FunctionSolver::evaluateFunction(double para)
{
    double arg = para;
    return (func)->invokeFunction(&arg, sizeof(para) / sizeof(double));
}

double BisectionFunctionSolver::BisectionMethod(bool isSilent)
{
    if(isSetUp())
    {
	double interval, mid, lBound, uBound, lValue, uValue, mValue;
	int i;
	lBound = lowerBound;
	uBound = upperBound;
	interval = uBound - lBound;

	//while(i < iteration && abs(mValue = evaluateFunction(mid)) < ignorance)
	for(i = 0; i < iteration; i++)
	{
	    interval /= 2;
	    mid = lBound + interval;
	    mValue = evaluateFunction(mid);
	    lValue = evaluateFunction(lBound);
	    uValue = evaluateFunction(uBound);

	    if(interval < ignorance || mValue < ignorance)
		break;

	    if(sign(mValue) == sign(lValue))
	    {
		lBound = mid;
		lValue = mValue;
	    }
	    else
	    {
		uBound = mid;
		uValue = mValue;
	    }

	    if(!isSilent)
	    {
		std::cout << "At iteration " << i << " the function value at x = " << mid << " is " << mValue << endl;
	    }
	}

	return mid;
    }
}

BisectionFunctionSolver::BisectionFunctionSolver():FunctionSolver()
{}
BisectionFunctionSolver::~BisectionFunctionSolver()
{}

NewtonFunctionSolver::NewtonFunctionSolver():FunctionSolver()
{
    first_prime = NULL;
}
NewtonFunctionSolver::~NewtonFunctionSolver(){}

void NewtonFunctionSolver::setFirstPrime(Function *func)
{
    if(func != NULL)
        first_prime = func;
}

double NewtonFunctionSolver::evaluateFirstPrime(double val)
{
    double arg = val;
    //return ((Function1v*)first_prime)->invokeFunction(val);
    return (first_prime)->invokeFunction(&arg, sizeof(arg) / sizeof(double));
}

bool NewtonFunctionSolver::isSetUp()
{
    return FunctionSolver::isSetUp() && first_prime != NULL;
}

double NewtonFunctionSolver::NewtonMethod(double ini_x, bool isSilenet)
{

    if(isSetUp())
    {
	double fval;
	double new_x;

	fval = evaluateFunction(ini_x);
	if(!isSilenet)
            std::cout << "At iteration " << 0 << " the function value at x = " << ini_x << " is " << fval << endl;
	if(util::abs(fval) < ignorance)
	{
	    return ini_x;
	}

	for(int i = 0; i < iteration; i++)
	{
	    //double denominator = evaluateFirstPrime(ini_x);
	    double denominator = first_prime->invokeFunction(&ini_x, 1);
	    if(denominator == 0) 
		throw(overflow_error("zero division\n"));

	    new_x = ini_x - fval / evaluateFirstPrime(ini_x); 
	    
	    fval = evaluateFunction(new_x);

	    if(!isSilenet)
		std::cout << "At iteration " << i << " the function value at x = " << new_x << " is " << fval << endl;
	    
	    
	    if(util::abs(new_x - ini_x) < ignorance || fval < ignorance)
		break;

	    ini_x = new_x;
	}

	return new_x;
    }
}

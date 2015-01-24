#include "FunctionSolver.h"
#include "Function.h"

FunctionSolver::FunctionSolver()
{
    func = NULL;
    isFunctionSet = isIterationSet = isBoundSet = isIgnoranceSet = isPrecisionSet = isSegmentSet = false;
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

void FunctionSolver::setBound(double lb, double ub)
{
    assert(lb <= ub);
    lowerBound = lb;
    upperBound = ub;

    isBoundSet = true;
}
void FunctionSolver::setFunction(Function *f)
{
    if(f != NULL)
	func = f;
    isFunctionSet = true;
}

void FunctionSolver::setPrecision(double pre)
{
    precision = pre;
    isPrecisionSet = true;
}

void FunctionSolver::setSegment(unsigned int s)
{
    segment = s;
    isSegmentSet = true;
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

double BisectionFunctionSolver::BisectionMethod(unsigned int s)
{
    if(!isSetUp())
	throw runtime_error("Bisection method: function not set up yet\n");
    
    double interval, mid, lBound, uBound, lValue, uValue, mValue;
    int i;
    lBound = lowerBound;
    uBound = upperBound;
    interval = uBound - lBound;

    //while(i < iteration && abs(mValue = evaluateFunction(mid)) < ignorance)
    lValue = evaluateFunction(lBound);
    uValue = evaluateFunction(uBound);

    if(util::sign(lValue) == util::sign(uValue))
    {
	cout << "No solution in the interval [" << lBound << ", " << uBound << "]\n";
	return lowerBound - 1;
    }

    for(i = 0; i < iteration; i++)
    {
	//update mid and midvalue if not converged
	interval /= 2;
	mid = lBound + interval;
	mValue = evaluateFunction(mid);

	//judge when converge
	if(util::abs(mValue) < ignorance)
	    return mid;
	if(interval < ignorance)
	    return lowerBound - 1;
	if(util::abs(lValue) < ignorance)
	    return lValue;
	if(util::abs(uValue) < ignorance)
	    return uValue;

	//update low or upper bound
	if(util::sign(mValue) != util::sign(lValue))
	{
	    uBound = mid;
	    uValue = mValue;
	}
	else if(util::sign(mValue) != util::sign(uValue))
	{
	    lBound = mid;
	    lValue = mValue;
	}

	if(!isSilent)
	{
	    std::cout << "At iteration " << i << " the function value at x = " << mid << " is " << mValue << endl;
	}

	lValue = evaluateFunction(lBound);
	uValue = evaluateFunction(uBound);
    }

    return lowerBound - 1;
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

double NewtonFunctionSolver::NewtonMethod(double ini_x, bool isSilent)
{

    if(isSetUp())
    {
	double fval;
	double new_x;

	fval = evaluateFunction(ini_x);
	if(!isSilent)
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

	    if(!isSilent)
		std::cout << "At iteration " << i << " the function value at x = " << new_x << " is " << fval << endl;
	    
	    
	    if(util::abs(new_x - ini_x) < ignorance || fval < ignorance)
		break;

	    ini_x = new_x;
	}

	return new_x;
    }
}

SecantFunctionSolver::SecantFunctionSolver():FunctionSolver()
{}
SecantFunctionSolver::~SecantFunctionSolver()
{}

double SecantFunctionSolver::SecandMethod(bool isSilent)
{
    double lBound, uBound, lValue, uValue, derivative, denominator; 
    lBound = lowerBound;
    uBound = upperBound;

    lValue = evaluateFunction(lBound);
    uValue = evaluateFunction(uBound);

    for(int i = 0; i < iteration - 2; i++)
    {
	if(util::abs(lValue) < util::abs(uValue))
	{
	    util::swap(lValue, uValue);
	    util::swap(lBound, uBound);
	}

	denominator = uValue - lValue;
	if(denominator == 0)
	    throw overflow_error("divide by zero\n");

	derivative = (uBound - lBound) / denominator;
	lBound = uBound;
	lValue = uValue;

	uBound -= uValue * derivative;
	uValue = evaluateFunction(uBound);

	if(!isSilent)
            std::cout << "At iteration " << i << " the function value at x = " << uBound << " is " << uValue << endl;

	if(util::abs(uValue) < ignorance || util::abs(uBound - lBound) < ignorance)
	    break;
    }

    return uBound;
}

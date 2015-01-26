#include "FunctionSolver.h"

void FunctionSolver::printConditions()
{
    cout << endl;
    cout << "Ignorance : ";
    cout << ignorance << endl;
    cout << "Precision : ";
    cout << precision << endl;
    cout << "Interval  : [";
    cout << setw(4) << setfill(' ') << lowerBound;
    cout << " ,";
    cout << setw(4) << setfill(' ') << upperBound;
    cout << " ] (Interval only means where it begins iterating)\n";
    cout << "Segment   : ";
    cout << segment << endl;
    cout << "Iteration : ";
    cout << iteration << endl;

}
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

void BisectionFunctionSolver::solve()
{
    cout << " Bisection Method solving " + func->toString() << endl;
    if(!isSetUp())
	throw runtime_error("Bisection method: function not set up yet\n");
    printConditions();
    for(unsigned int s = 0; s < segment; s++)
    {
	double l, seg, result;
	seg = (upperBound - lowerBound) / segment;
	l = lowerBound + s * seg;

	cout << "[ ";
	cout << setw(4) << setfill(' ') << l;
	cout << ", ";
	cout << setw(4) << setfill(' ') << l + seg;
	cout << " ]\n";

	try
	{
	    result = BisectionMethod(s);
	}
	catch(overflow_error e)
	{
	    cout << "x = N/A" << endl;
	    continue;
	}

	if(result < lowerBound)
	    cout << "x = N/A" << endl;
	else
	{
	    cout << "x = "; 
	    cout << setw(4) << setfill(' ') << result << endl;
	}
    }
}

BisectionFunctionSolver& BisectionFunctionSolver::operator= (const BisectionFunctionSolver&) {return *this;}
double BisectionFunctionSolver::BisectionMethod(unsigned int s)
{
    
    double seg, interval, mid, lBound, uBound, lValue, uValue, mValue;

    seg = (upperBound - lowerBound) / segment;
    lBound = lowerBound + s * seg;
    uBound = lowerBound + (s+1) * seg;
    interval = seg;

    //while(i < iteration && abs(mValue = evaluateFunction(mid)) < ignorance)
    lValue = evaluateFunction(lBound);
    uValue = evaluateFunction(uBound);

    if(util::sign(lValue) == util::sign(uValue))
	return lowerBound - 1;

    for(unsigned i = 0; i < iteration; i++)
    {
	//update mid and midvalue if not converged
	interval /= 2;
	mid = lBound + interval;
	mValue = evaluateFunction(mid);

	//judge when converge
	if(util::abs(mValue) < precision)
	    return mid;
	if(interval < ignorance)
	    return lowerBound - 1;
	if(util::abs(lValue) < precision)
	    return lValue;
	if(util::abs(uValue) < precision)
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
	//cout << "At iteration " << i << " the function value at x = " << mid << " is " << mValue << endl;

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

NewtonFunctionSolver& NewtonFunctionSolver::operator= (const NewtonFunctionSolver&) {return *this;}
void NewtonFunctionSolver::solve()
{
    cout << " Newton Method solving " + func->toString() << endl;
    if(!isSetUp())
	throw runtime_error("Newton method: function not set up yet\n");

    printConditions();
    for(unsigned int s = 0; s < segment; s++)
    {
	double l, seg, result;
	seg = (upperBound - lowerBound) / segment;
	l = lowerBound + s * seg;

	cout << "[ ";
	cout << setw(4) << setfill(' ') << l;
	cout << ", ";
	cout << setw(4) << setfill(' ') << l + seg;
	cout << " ]\n";

	try
	{
	    result = NewtonMethod(s + seg / 2);
	}
	catch(overflow_error e)
	{
	    cout << "x = N/A" << endl;
	    continue;
	}

	if(result < lowerBound)
	    cout << "x = N/A" << endl;
	else
	{
	    cout << "x = "; 
	    cout << setw(4) << setfill(' ') << result << endl;
	}
    }
}

double NewtonFunctionSolver::NewtonMethod(double ini_x)
{

    double fval;
    double new_x;

    fval = evaluateFunction(ini_x);

    if(util::abs(fval) < precision)
	return ini_x;

    for(unsigned int i = 0; i < iteration; i++)
    {
	//double denominator = evaluateFirstPrime(ini_x);
	double denominator = first_prime->invokeFunction(&ini_x, 1);
	if(denominator == 0) 
	    throw(overflow_error("zero division\n"));

	new_x = ini_x - fval / evaluateFirstPrime(ini_x); 

	fval = evaluateFunction(new_x);

	if(fval < ignorance)
	    return new_x;
	if(util::abs(new_x - ini_x) < ignorance)
	    return lowerBound - 1;

	ini_x = new_x;
    }
    return new_x;
}

SecantFunctionSolver& SecantFunctionSolver::operator= (const SecantFunctionSolver&) {return *this;}
SecantFunctionSolver::SecantFunctionSolver():FunctionSolver()
{}
SecantFunctionSolver::~SecantFunctionSolver()
{}
void SecantFunctionSolver::solve()
{
    cout << " Secant Method solving " + func->toString() << endl;
    if(!isSetUp())
	throw runtime_error("Secant method: function not set up yet\n");

    printConditions();
    for(unsigned int s = 0; s < segment; s++)
    {
	double l, seg, result;
	seg = (upperBound - lowerBound) / segment;
	l = lowerBound + s * seg;

	cout << "[ ";
	cout << setw(4) << setfill(' ') << l;
	cout << ", ";
	cout << setw(4) << setfill(' ') << l + seg;
	cout << " ]\n";

	try
	{
	    result = SecandMethod(s);
	}
	catch(overflow_error e)
	{
	    cout << "x = N/A" << endl;
	    continue;
	}

	if(result < lowerBound)
	    cout << "x = N/A" << endl;
	else
	{
	    cout << "x = "; 
	    cout << setw(4) << setfill(' ') << result << endl;
	}
    }
}

double SecantFunctionSolver::SecandMethod(unsigned int s)
{
    double seg, lBound, uBound, lValue, uValue, derivative, denominator; 
    seg = (upperBound - lowerBound) / segment;

    lBound = lowerBound + s * seg;
    uBound = lowerBound + seg;

    lValue = evaluateFunction(lBound);
    uValue = evaluateFunction(uBound);

    for(unsigned int i = 0; i < iteration - 2; i++)
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


	if(util::abs(uValue) < precision)
	    return uBound;
	if( util::abs(uBound - lBound) < ignorance)
	    return lowerBound - 1;
    }
    return lowerBound - 1;
}

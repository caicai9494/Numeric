#include "Function.h"
#include "FunctionSolver.h"
#include "common/util.h"
#include <cmath>

using namespace std;


double func(double *para, unsigned int N);
double func2(double *para, unsigned int N);
double func3(double *para, unsigned int N);
double func3_prime(double *para, unsigned int N);

int main()
{
    Function1v *func1v = new Function1v();
    func1v->setFuncPtr(&func);
    double arg = 0.0;
    std::cout << func1v->invokeFunction(&arg) << endl;

    Function1v *func1v2 = new Function1v();
    func1v2->setFuncPtr(&func2);
    arg = 5;
    std::cout << func1v2->invokeFunction(&arg) << endl;

    /*
    delete func1v;
    func1v = NULL;
    std::cout << func1v->invokeFunction(0) << endl;
    */

    BisectionFunctionSolver *bSolver = new BisectionFunctionSolver();
    bSolver->setFunction(func1v);
    delete bSolver;
    delete func1v;
    delete func1v2;
    func1v = NULL;

    Function1v func2v;
    func2v.setFuncPtr(&func);

    Function1v func3v;
    func3v.setFuncPtr(&func2);

    BisectionFunctionSolver *bSolver2 = new BisectionFunctionSolver();
    bSolver2->setFunction(&func2v);
    delete bSolver2;
    arg = 1.0;
    func2v.invokeFunction(&arg);

    //solve 2x + 5 = 0
    BisectionFunctionSolver *bSolver3 = new BisectionFunctionSolver();
    bSolver3->setFunction(&func2v);
    assert(bSolver3->isSetUp() == false);
    bSolver3->setIgnorance(0.001);
    bSolver3->setIteration(100);
    bSolver3->setBound(-10, 20);
    assert(bSolver3->isSetUp() == true);
    //cout << bSolver3->evaluateFunction(0) << endl;
    //cout << bSolver3->evaluateFunction(3) << endl;
    
    end_timer();
    start_timer();
    cout << bSolver3->BisectionMethod(false) << endl;
    start_timer();
    end_timer();

    //solve x - sinx = 0
    Function1v func4v;
    func4v.setFuncPtr(&func3);

    bSolver3->setFunction(&func4v);
    bSolver3->setIgnorance(0.0001);
    bSolver3->setIteration(100);
    bSolver3->setBound(-10, 11);

    start_timer();
    cout << bSolver3->BisectionMethod(false) << endl;
    end_timer();
    delete bSolver3;

    assert(util::abs(5) == 5);
    assert(util::abs(5.99) == 5.99);
    assert(util::abs(-5.99) == 5.99);
    assert(util::abs(0) == 0);

    //solve x - sinx = 0
    Function1v func4v_prime;
    func4v_prime.setFuncPtr(&func3_prime);
    cout << " x - sinx = 0\n";
    arg = 4.0;
    cout << func4v.invokeFunction(&arg) << endl;

    NewtonFunctionSolver *nSolver1 = new NewtonFunctionSolver();
    nSolver1->setFunction(&func4v);
    nSolver1->setFirstPrime(&func4v_prime);
    nSolver1->setIgnorance(0.0001);
    nSolver1->setIteration(100);
    nSolver1->setBound(-10, 11);
    assert(nSolver1->isSetUp() == true);

    start_timer();
    try
    {
        cout << nSolver1->NewtonMethod(0.5, false) << endl;
    }
    catch(std::overflow_error &e)
    {
	std::cout << "standard exception :" << e.what(); 
    }
    end_timer();
    delete nSolver1;

    double val1, val2;
    val1 = 1;
    val2 = 2;
    util::swap(val1, val2);
    cout << "val1 = " << val1 << endl;
    cout << "val2 = " << val2 << endl;

    SecantFunctionSolver *sSolver1 = new SecantFunctionSolver();
    sSolver1->setFunction(&func4v);
    sSolver1->setIgnorance(0.0001);
    sSolver1->setIteration(100);
    sSolver1->setBound(-10, 11);
    assert(sSolver1->isSetUp() == true);

    start_timer();
    try
    {
        cout << sSolver1->SecandMethod(false) << endl;
    }
    catch(std::overflow_error &e)
    {
	std::cout << "standard exception :" << e.what(); 
    }
    end_timer();
    delete sSolver1;

    return 0;
}

double func(double *para, unsigned int N)
{
    if(*para == 0) throw overflow_error("zero division\n");
    return 1 / *para;
}

double func2(double *para, unsigned int N)
{
    return 2 * (*para) + 5;
}

double func3(double *para, unsigned int N)
{
    return *para - sin(*para);
}
double func3_prime(double *para, unsigned int N)
{
    return 1 - cos(*para);
}

#include <FunctionSolver/Function.h>
#include <FunctionSolver/FunctionSolver.h>
#include <LinearAlgebra/Matrix.h>
#include <LinearAlgebra/Vector.h>
#include <LinearAlgebra/LinearEquationSolver.h>
#include <Approximating/Interpolation.h>
#include <common/util.h>
#include <common/Timer.h>
#include <cmath>
#include <vector>
#include <algorithm>

#define TEST_MATRIX 1
#define TEST_FUNC 1
#define TEST_INTP 1

using namespace std; 
using namespace Numeric; 


// y = 1 / x
double func(double *para, unsigned int N);

// y = 2 x + 5
double func2(double *para, unsigned int N); 

// y = x - sin(x);
double func3(double *para, unsigned int N);

// y = 1 - cos(x);
double func3_prime(double *para, unsigned int N);

// y = x^3 - x - 1;
double func4(double *para, unsigned int N);

int main()
{

#if(TEST_FUNC)
    Function1v *func1v = new Function1v();
    func1v->setFuncPtr(&func);
    double arg = 0.0;
    try
    {
        std::cout << func1v->invokeFunction(&arg) << endl;
    }
    catch(overflow_error e)
    {
	std::cout << e.what() << endl;
    }

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

    // y = 1 / x
    Function1v func2v;
    func2v.setFuncPtr(&func);
    func2v.setFunctionString("Y = 1 / x");

    // y = 2x + 5
    Function1v func3v;
    func3v.setFuncPtr(&func2);
    func3v.setFunctionString("y = 2x + 5");

    //solve x - sinx = 0
    Function1v func4v;
    func4v.setFuncPtr(&func3);
    func4v.setFunctionString("y = x - sinx");

    //solve x^3 - x - 1 = 0
    Function1v func5v;
    func5v.setFuncPtr(&func4);
    func5v.setFunctionString("y = x^3 - x - 1");

    BisectionFunctionSolver *bSolver2 = new BisectionFunctionSolver();
    bSolver2->setFunction(&func2v);
    delete bSolver2;

    cout << " y = f(1.0)     1 / x\n";
    arg = 1.0;
    cout << func2v.invokeFunction(&arg);
    cout << endl;

    //solve 2x + 5 = 0
    BisectionFunctionSolver *bSolver3 = new BisectionFunctionSolver();
    bSolver3->setFunction(&func2v);
    assert(bSolver3->isSetUp() == false);
    bSolver3->setIgnorance(0.1);
    bSolver3->setIteration(100);
    bSolver3->setBound(-10, 20);
    bSolver3->setPrecision(0.1);
    bSolver3->setSegment(10);
    assert(bSolver3->isSetUp() == true);

    
    Timer::end_timer();
    Timer::start_timer();
    bSolver3->solve();
    cout << endl;

    bSolver3->setFunction(&func3v);
    bSolver3->solve();

    bSolver3->setFunction(&func4v);
    bSolver3->solve();

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
    nSolver1->setPrecision(0.001);
    nSolver1->setSegment(2);
    assert(nSolver1->isSetUp() == true);

    Timer::start_timer();
    nSolver1->solve();
    nSolver1->setFunction(&func5v);
    nSolver1->solve();
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
    sSolver1->setPrecision(0.0001);
    sSolver1->setSegment(10);
    assert(sSolver1->isSetUp() == true);

    Timer::start_timer();
    sSolver1->solve();
    Timer::end_timer();

    sSolver1->setFunction(&func5v);
    sSolver1->solve();
    delete sSolver1;
#endif
    
#if(TEST_MATRIX)

    unsigned int len = 5;
    Vector v1(len);
    for(unsigned int i = 0; i < len; i++)
	v1[i] = i;
    cout << " v1 : " << endl;
    cout << v1 << endl;

    Vector v3(len);
    for(unsigned int i = 0; i < len; i++)
	v3[i] = i + 3;
    cout << " v3 : " << endl;
    cout << v3 << endl;
    assert(v3 != v1);

    Vector v2(v1);
    cout << " v2 after copy v1: " << endl;
    cout << v2 << endl;
    assert(v2 == v1);

    v2 = v3;
    cout << " v2 after assigned by v3: " << endl;
    cout << v2 << endl;

    cout << " v2 product v3: " << endl;
    cout << v2.dot(v3) << endl;
    assert(v2.dot(v3) == 135);

    cout << " v2 times 2: " << endl;
    cout << v2 * 2 << endl;
    cout << " v2 times 4: " << endl;
    cout << (2 * v2) * 2 << endl;
    cout << 2 * (2 * v2) << endl;
    cout << " v2 times 22.44: " << endl;
    cout << (2 * v2) * 11.22 << endl;
    cout << 11.22 * (2 * v2) << endl;

    cout << " v2 times 22.44 + v3: " << endl;
    cout << ((2 * v2) * 11.22) + v3 << endl;

    cout << " v2 times 22.44 + v3: " << endl;
    cout << ((2 * v2) * 11.22) - v3 << endl;

    cout << " v2 == v3: " << endl;
    cout << v2 << endl;
    cout << v3 << endl;
    assert((v2 == v3));

    Vector v7 = Vector::zeros(3);
    Vector v8 = Vector::zeros(5);
    assert(v7 != v8);

    Vector v5(5);
    v5 = v2.transpose();
    cout << "transpose v2 " << endl;
    cout << v5 << endl;

    cout << "3 rows and 4 cols    3 X 4" << endl;
    Matrix m1(3,4);
    //Matrix m2(-3,-4);
    for(int i = 0; i < 3; i++)
    {
	for(int j = 0; j < 4; j++)
	{
	    m1[i][j] = i + j;
	}
    }

    cout << m1;

    assert(m1[0][0] == 0);
    assert(m1[0][1] == 1);
    assert(m1[0][2] == 2);
    assert(m1[0][3] == 3);
    assert(m1[1][0] == 1);
    assert(m1[1][1] == 2);
    assert(m1[1][2] == 3);
    assert(m1[1][3] == 4);
    assert(m1[2][0] == 2);
    assert(m1[2][1] == 3);
    assert(m1[2][2] == 4);
    assert(m1[2][3] == 5);

    cout << "m1 transpose \n";
    cout << m1.transpose() << endl;

    cout << "m2 copy from m1 \n";
    Matrix m2(m1.transpose());
    cout << m2;
    assert(!m2.isSquare());

    cout << "m1' transpose \n";
    m1 = m1.transpose();
    cout << m1.transpose() << endl;
    assert(!m1.isSquare());

    cout << "m1' * m2\n";
    cout << m1.transpose() * m2;

    cout << " let m2 = m1\n";
    cout << (m2 = m1);

    cout << "let 2.2(m2 + m1) - m2\n";
    cout << (m2 + m1)*2.2 - m2;

    cout << "v1\n";
    cout << v1 << endl;
    cout << "v2\n";
    cout << v2 << endl;

    cout << "v2 * v1 * 2.22\n";
    Matrix m6 = v2 * v1 * 2.22;
    assert(m6.isSquare());
    cout << m6;
    assert(!m6.isSymmetric());
    assert(!m6.isDiagonal());
    assert(!m6.isUpperTriangle());
    assert(!m6.isLowerTriangle());

    cout << " m 5 = v2' * (v2 * v1 * 2.22)\n";
    Matrix m5 = v2.transpose() * (v2 * v1 * 2.22);
    cout << m5;
    assert(!m5.isSymmetric());
    assert(!m5.isDiagonal());
    assert(!m5.isUpperTriangle());
    assert(!m5.isLowerTriangle());

    cout << " m5 * v2'\n";
    cout << m5 * v2.transpose() << endl;

    cout << "zeros vector of 5\n";
    cout << Vector::zeros(5) << endl;

    cout << "zeros matrix of 5 * 3\n";
    Matrix m3 = Matrix::zeros(5,3);
    cout << m3;
    assert(!m3.isSymmetric());
    assert(!m3.isDiagonal());
    assert(!m3.isUpperTriangle());
    assert(!m3.isLowerTriangle());
    assert(!m3.isSquare());

    cout << "identity matrix of 5 * 5\n";
    Matrix m4 = Matrix::identity(5);
    cout << m4;
    assert(m4.isSymmetric());
    assert(m4.isDiagonal());
    assert(m4.isUpperTriangle());
    assert(m4.isLowerTriangle());
    assert(m4 != m3);
    assert(m4.isSquare());

    cout << " lower triangle matrix\n";
    Matrix lm = Matrix::zeros(5, 5);
    for(unsigned int i = 0; i < 5; i++)
	for(unsigned int j = 0; j <= i; j++)
	    lm[i][j] = i + 4;
    cout << lm;
    assert(!lm.isSymmetric());
    assert(!lm.isDiagonal());
    assert(!lm.isUpperTriangle());
    assert(lm.isLowerTriangle());
    assert(m4.isSquare());

    cout << " upper triangle matrix\n";
    Matrix um = Matrix::zeros(5, 5);
    for(unsigned int i = 0; i < 5; i++)
	for(unsigned int j = i; j < 5; j++)
	    um[i][j] = i + 4;
    cout << um;
    assert(!um.isSymmetric());
    assert(!um.isDiagonal());
    assert(um.isUpperTriangle());
    assert(!um.isLowerTriangle());
    assert(um != lm);
    assert(Matrix::identity(5) == Matrix::identity(5));
    assert(m4.isSquare());

    cout << "swap um 2 row with 3 row\n";
    um.swapRow(1, 2);
    cout << um;

    cout << "swap um 3 row with 2 row\n";
    um.swapRow(2, 1);
    cout << um;

    cout << "swap um 2 col with 3 col\n";
    um.swapCol(1, 2);
    cout << um;

    cout << "swap um 3 row with 2 col\n";
    um.swapCol(2, 1);
    cout << um;

    cout << "lm * um\n";
    cout << lm * um;

    LinearEquationSolver lSolver3;
    lSolver3.setLhsMatrix(lm);
    assert(!lSolver3.isHomogeneous());

    Vector res_zero = Vector::zeros(5);

    LinearEquationSolver lSolver;
    lSolver.setLhsMatrix(um);
    lSolver.setRhsVector(res_zero);
    cout << lSolver;
    assert(lSolver.isHomogeneous());

    Vector res_2 = Vector::zeros(5);
    res_2[2] = 2;
    res_2.swap(2,0);

    LinearEquationSolver lSolver2;
    lSolver2.setLhsMatrix(lm);
    lSolver2.setRhsVector(res_2);
    cout << lSolver2;
    assert(!lSolver2.isHomogeneous());
    cout << " result is\n";
    Timer::start_timer();
    cout << lSolver2.solve() << endl;
    Timer::end_timer();

    Vector vanvector(3);
    vanvector[0] = 1;
    vanvector[1] = 2;
    vanvector[2] = 3;
    cout << " vandermonde matrix\n";
    Matrix van = Matrix::vandermonde(v2);
    cout << van;
    assert(!van.isSymmetric());
    assert(!van.isDiagonal());
    assert(!van.isUpperTriangle());
    assert(!van.isLowerTriangle());
    assert(van.isSquare());
    LinearEquationSolver vansolver;
    vansolver.setLhsMatrix(van);
    vansolver.setRhsVector(v2);
    cout << "solve van and vanvector\n";
    cout << vansolver.solve() << endl;
    //vansolver.GaussElimitation();
    Matrix vl = vansolver.getL();
    Matrix vu = vansolver.getU();
    cout << " van's lower triangle matrix\n";
    cout << vl;
    cout << " van's upper triangle matrix\n";
    cout << vu;
    cout << " van's \n";
    cout << vl * vu << endl;

    Matrix trickym = Matrix::zeros(3, 3);
    trickym[0][0] = 0.001;
    trickym[0][1] = 2.00;
    trickym[0][2] = 3.00;
    trickym[1][0] = -1.00;
    trickym[1][1] = 3.712;
    trickym[1][2] = 4.623;
    trickym[2][0] = -2.00;
    trickym[2][1] = 1.072;
    trickym[2][2] = 5.643;
    Vector trickrhs = Vector::zeros(3);
    trickrhs[0] = 1;
    trickrhs[1] = 2;
    trickrhs[2] = 3;
    assert(!trickym.isSymmetric());
    assert(!trickym.isDiagonal());
    assert(!trickym.isUpperTriangle());
    assert(!trickym.isLowerTriangle());
    assert(trickym.isSquare());
    LinearEquationSolver trickySolver;
    trickySolver.setLhsMatrix(trickym);
    trickySolver.setRhsVector(trickrhs);
    trickySolver.solve();
    vl = trickySolver.getL();
    vu = trickySolver.getU();
    cout << trickym;
    cout << " trickym's lower triangle matrix\n";
    cout << vl;
    cout << " trickym's upper triangle matrix\n";
    cout << vu;
    cout << " trickym's \n";
    cout << vl * vu << endl;
    cout << "result is !trickym's \n";
    cout << trickySolver.solve() << endl;

    cout << " van\n";
    cout << van;
    cout << " van's inverse\n";
    Matrix ivan = van.inverse();
    cout << ivan;
    cout << " check \n";
    cout << van * ivan;

    cout << " trickym's inverse\n";
    Matrix invtricky = trickym.inverse();
    cout << invtricky;
    cout << "check\n";
    cout << invtricky * trickym;
#endif

#if(TEST_INTP)
    typedef vector<Point2D*> PointVector;
    typedef vector<Point2D*>::iterator IT;
    PointVector pVector;
    pVector.push_back(new Point2D(1,2));
    pVector.push_back(new Point2D(3,2));
    pVector.push_back(new Point2D(-3,2));
    sort(pVector.begin(), pVector.end(), less<Point2D*>());

    for(int i = 0; i < 3; i++)
	cout << *(pVector.at(i));
    for(IT it = pVector.begin(); it != pVector.end(); it++)
	delete *it;

    NewtonInterpolation newtonIntp;
    Point2D p1(5, 1);
    Point2D p2(-7, -23);
    Point2D p3(-6, -54);
    Point2D p4(0, -954);
    newtonIntp.addPoint(p1);
    newtonIntp.addPoint(p2);
    newtonIntp.addPoint(p3);
    newtonIntp.addPoint(p4);
    assert(newtonIntp.interpolate(0) == -954);
    assert(newtonIntp.interpolate(5) == 1);
    assert(newtonIntp.interpolate(-7) == -23);
    assert(newtonIntp.interpolate(-6) == -54);

    NewtonInterpolation newtonIntp2;
    vector<Point2D> pV;
    pV.push_back(p1);
    pV.push_back(p2);
    pV.push_back(p3);
    pV.push_back(p4);
    newtonIntp2.addPointArray(pV);
    assert(newtonIntp2.interpolate(0) == -954);
    assert(newtonIntp2.interpolate(5) == 1);
    assert(newtonIntp2.interpolate(-7) == -23);
    assert(newtonIntp2.interpolate(-6) == -54);
    cout << newtonIntp2 << endl;

    NewtonInterpolation newtonIntp3;
    for(int i = 0; i < 40; i++)
    {
	static double args= -1;
	args += 0.2 * i;
	double val = func3(&args, 1);

	Point2D temp(args, val);
	newtonIntp3.addPoint(temp);
    }
    //cout << newtonIntp3 << endl;

    double argfunc = 0.5;
    cout << "real value:\n";
    cout << func3(&argfunc, 1);
    cout << endl;
    cout << "interpolated value:\n";
    cout << newtonIntp3.interpolate(argfunc);
    cout << endl;

    LagrangeInterpolation lIntp1;
    lIntp1.addPoint(p1);
    lIntp1.addPoint(p2);
    lIntp1.addPoint(p3);
    lIntp1.addPoint(p4);
    assert(lIntp1.interpolate(p1.x) == p1.y);
    assert(lIntp1.interpolate(p2.x) == p2.y);
    assert(lIntp1.interpolate(p3.x) == p3.y);
    assert(lIntp1.interpolate(p4.x) == p4.y);

    LagrangeInterpolation lIntp2;
    for(int i = 0; i < 40; i++)
    {
	static double args= -1;
	args += 0.2 * i;
	double val = func3(&args, 1);

	Point2D temp(args, val);
	lIntp2.addPoint(temp);
    }
    //double argfunc = 0.5;
    cout << "real value:\n";
    cout << func3(&argfunc, 1);
    cout << endl;
    cout << "interpolated value:\n";
    cout << lIntp2.interpolate(argfunc);
    cout << endl;
    //cout << lIntp2 << endl;
    
#endif
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
double func4(double *para, unsigned int N)
{
    return (*para) * (*para) * (*para) - (*para) - 1;
}

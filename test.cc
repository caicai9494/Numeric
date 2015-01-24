#include "FunctionSolver/Function.h"
#include "FunctionSolver/FunctionSolver.h"
#include "LinearAlgebra/Matrix.h"
#include "LinearAlgebra/Vector.h"
#include "LinearAlgebra/LinearEquationSolver.h"
#include "common/util.h"
#include <cmath>

using namespace std; 

double func(double *para, unsigned int N);
double func2(double *para, unsigned int N); double func3(double *para, unsigned int N);
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
    start_timer();
    cout << lSolver2.solve() << endl;
    end_timer();

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
    //GaussElimitation();
    Matrix vl = van.getL();
    Matrix vu = van.getU();
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
    trickym.GaussElimitation();
    vl = trickym.getL();
    vu = trickym.getU();
    cout << trickym;
    cout << " trickym's lower triangle matrix\n";
    cout << vl;
    cout << " trickym's upper triangle matrix\n";
    cout << vu;
    cout << " trickym's \n";
    cout << vl * vu << endl;
    lSolver2.setLhsMatrix(trickym);
    lSolver2.setRhsVector(trickrhs);
    cout << "result is !trickym's \n";
    cout << lSolver2.solve() << endl;

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

#ifndef _LINEAREQUATIONSOLVER_H
#define _LINEAREQUATIONSOLVER_H
#include "Matrix.h"
#include "Vector.h"
#include <stdexcept>

using namespace std;

namespace Numeric
{

    class LinearEquationSolver
    {
	public:
	    LinearEquationSolver();
	    //Solve square non-singular matrix
	    //throw overflow_error is non-square or non-singular
	    Vector solve();

	    //local copy of matrix and vector
	    void setLhsMatrix(Matrix &m);
	    void setRhsVector(Vector &v);

	    bool isHomogeneous();

	    //delete Matrix and vector yourself
	    //delete luDecomposition
	    ~LinearEquationSolver();

	    friend ostream& operator<<(ostream &stream, LinearEquationSolver& lSolver);

	    Matrix getL();
	    Matrix getU();

	    //using pivoting
	    //throw runtime_error if zeros at diagonal cannot be solved
	    void GaussElimitation();
	private:
	    Matrix *lhsMatrix;
	    Vector *rhsVector;
	    LUDecomposition *luDecomposition;

	    bool isLegalEquation();

	    LinearEquationSolver& operator= (const LinearEquationSolver&);

	    Vector solveUpperTriangle();
	    Vector solveLowerTriangle();
	    Vector solveDiagonal();

    };
}

#endif

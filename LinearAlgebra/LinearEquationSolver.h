#ifndef _LINEAREQUATIONSOLVER_H
#define _LINEAREQUATIONSOLVER_H
#include "Matrix.h"
#include "Vector.h"
#include <stdexcept>

using namespace std;

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

	//delete local copy of matrix and vector
	~LinearEquationSolver();

	friend ostream& operator<<(ostream &stream, LinearEquationSolver& lSolver);
    private:
	Matrix *lhsMatrix;
	Vector *rhsVector;
	bool isLegalEquation();

	LinearEquationSolver& operator= (const LinearEquationSolver&) {}

	Vector solveUpperTriangle();
	Vector solveLowerTriangle();
	Vector solveDiagonal();
};

#endif

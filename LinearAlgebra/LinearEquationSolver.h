#ifndef _LINEAREQUATIONSOLVER_H
#define _LINEAREQUATIONSOLVER_H
#include "Matrix.h"
#include "Vector.h"

using namespace std;

class LinearEquationSolver
{

    public:
	LinearEquationSolver();
	Vector solve();

	void setLhsMatrix(Matrix &m);
	void setRhsVector(Vector &v);

	bool isHomogeneous();

	~LinearEquationSolver();
    private:
	Matrix *lhsMatrix;
	Vector *rhsVector;
	bool isLegalEquation();

	LinearEquationSolver& operator= (const LinearEquationSolver&) {}
};
#endif

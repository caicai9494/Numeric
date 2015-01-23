#include "LinearEquationSolver.h"


LinearEquationSolver::LinearEquationSolver() 
{
    lhsMatrix = NULL;
    rhsVector = NULL;
}

LinearEquationSolver::~LinearEquationSolver() {}

void LinearEquationSolver::setLhsMatrix(Matrix &m)
{
    if(&m != NULL)
        lhsMatrix = &m;
}

void LinearEquationSolver::setRhsVector(Vector &v)
{
    if(&v != NULL)
	rhsVector = &v;
}

bool isLegalEquation()
{
    if(!rhsVector || !lhsMatrix)
	return false;

    if(lhsMatrix->getCol() != rhsVector->getDim())
	return false;
    else
	return true;
}

bool LinearEquationSolver::isHomogeneous()
{
    if(!isLegalEquation())
	return false;

    if(*rhsVector == Vector::zeros(rhsVector->getDim()))
	return true;
}


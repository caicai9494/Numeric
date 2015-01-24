#include "LinearEquationSolver.h"


LinearEquationSolver::LinearEquationSolver() 
{
    lhsMatrix = NULL;
    rhsVector = NULL;
}

LinearEquationSolver::~LinearEquationSolver() 
{
    /*
    if(! lhsMatrix)
        delete lhsMatrix;
    if(! rhsVector)
    delete rhsVector;
    */
}

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


bool LinearEquationSolver::isLegalEquation()
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
    else
	return false;
}

ostream& operator<<(ostream &stream, LinearEquationSolver& lSolver)
{
    stream << "left hand side matrix\n";
    stream << *(lSolver.lhsMatrix);
    stream << "right hand side vector\n";
    stream << *(lSolver.rhsVector) << endl;

    return stream;
}

Vector LinearEquationSolver::solve()
{   //assert square matrix

    assert(lhsMatrix->isSquare());
    assert(isLegalEquation());

    if(isHomogeneous())
    {
	//if r(matrix) = R
	//return zeros
	if(lhsMatrix->getR() == lhsMatrix->getRow())
	    return Vector::zeros(lhsMatrix->getRow());
	else
	    throw overflow_error("Cannot solve: Non singular matrix\n");
	//else
	//return any vector
    }
    else
    {
	if(lhsMatrix->isDiagonal())
	    return solveDiagonal();
	else if(lhsMatrix->isLowerTriangle())
	    return solveLowerTriangle();
	//else if pivoting
	else if(lhsMatrix->isUpperTriangle())
	    return solveUpperTriangle();
	else
	{
	    lhsMatrix->GaussElimitation();
	    Matrix L = lhsMatrix->getL();
	    Matrix U = lhsMatrix->getU();
	    
	    LinearEquationSolver temp;
	    Matrix copy_lhs = L;
	    Vector copy_rhs = *rhsVector;
	    temp.setLhsMatrix(copy_lhs);
	    temp.setRhsVector(copy_rhs);
	    Vector rhs2 = temp.solveLowerTriangle();
	    copy_lhs = U;

	    temp.setLhsMatrix(copy_lhs);
	    temp.setRhsVector(rhs2);
	    Vector res = temp.solveUpperTriangle();
	    return res;
	}
    }
}

Vector LinearEquationSolver::solveDiagonal()
{
    unsigned int dim = rhsVector->getDim();

    Vector res = Vector::zeros(dim);

    for(unsigned int i = 0; i < dim; i++)
    {
	double nominator = (*rhsVector)[i];
	double denominator = (*lhsMatrix)[i][i];
	if(!nominator)  
	    res[i] = 0;
	else if(!denominator)
	    throw overflow_error("Cannot solve: Non singular diagonal matrix\n");
	else
	    res[i] = nominator / denominator;
    }

    return res;
}
Vector LinearEquationSolver::solveLowerTriangle()
{
    unsigned int dim = rhsVector->getDim();

    Vector res = Vector::zeros(dim);

    for(unsigned int i = 0; i < dim; i++)
    {
	double denominator = (*lhsMatrix)[i][i];
	if(!denominator)
	    throw overflow_error("Cannot solve: Non singular lower triangle matrix\n");

        for(unsigned int j = 0; j < i; j++)
	{
	    res[i] -= (*lhsMatrix)[i][j] * res[j];
	}
	res[i] = (res[i] + (*rhsVector)[i]) / denominator;
    }
    return res;
}

Vector LinearEquationSolver::solveUpperTriangle()
{
    unsigned int dim = rhsVector->getDim();

    Vector res = Vector::zeros(dim);

    for(int i = dim - 1; i >= 0; i--)
    {
	double denominator = (*lhsMatrix)[i][i];
	if(!denominator)
	    throw overflow_error("Cannot solve: Non singular upper triangle matrix\n");

        for(int j = dim - 1; j > i; j--)
	{
	    res[i] -= (*lhsMatrix)[i][j] * res[j];
	}
	res[i] = (res[i] + (*rhsVector)[i]) / denominator;
    }
    return res;
}

#include "LinearEquationSolver.h"


LinearEquationSolver& LinearEquationSolver::operator= (const LinearEquationSolver&) {return *this;}
LinearEquationSolver::LinearEquationSolver() 
{
    lhsMatrix = NULL;
    rhsVector = NULL;
    luDecomposition = NULL;
}

LinearEquationSolver::~LinearEquationSolver() 
{
    /*
    if(! lhsMatrix)
        delete lhsMatrix;
    if(! rhsVector)
    delete rhsVector;
    */
    if(luDecomposition)
	delete luDecomposition;
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
	    GaussElimitation();

	    Matrix L = getL();
	    Matrix U = getU();

	    LinearEquationSolver tempSolver;
	    Matrix copy_lhs = L;
	    Vector copy_rhs = *rhsVector;
	    tempSolver.setLhsMatrix(copy_lhs);
	    tempSolver.setRhsVector(copy_rhs);
	    Vector rhs2 = tempSolver.solveLowerTriangle();
	    copy_lhs = U;

	    tempSolver.setLhsMatrix(copy_lhs);
	    tempSolver.setRhsVector(rhs2);
	    Vector res = tempSolver.solveUpperTriangle();
	    return res;
	    /*
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
	    */
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
Matrix LinearEquationSolver::getL()
{
    assert(luDecomposition != NULL);
    return *(luDecomposition->LMatrix);
}
Matrix LinearEquationSolver::getU()
{
    assert(luDecomposition != NULL);
    return *(luDecomposition->UMatrix);
}
void LinearEquationSolver::GaussElimitation()
{
    assert(lhsMatrix->isSquare());

    if(luDecomposition != NULL)
	delete luDecomposition;

    unsigned int row = lhsMatrix->getRow();
    Matrix L = Matrix::identity(row);
    Matrix U = Matrix::zeros(row, row);

    luDecomposition = new LUDecomposition(row);

    double sum = 0;

    for(unsigned int i = 0; i < row; i++)
    {

        unsigned int max_r;
        double max_val;
        max_r = i;
        max_val = (*lhsMatrix)[i][i];

	for(unsigned int r = i; r < row; r++)
	{
	    if(max_val < (*lhsMatrix)[r][i])
	    {
		max_val = (*lhsMatrix)[r][i];
		max_r = r;
	    }
	}

	if(max_r != i)
	{
	    (*lhsMatrix).swapRow(max_r, i);
	    (*rhsVector).swap(max_r, i);
	}

	for(unsigned int j = 0; j < i; j++)
	{
	    sum += L[i][j] * U[j][i];
	}
    
	U[i][i] = (*lhsMatrix)[i][i] - sum;	
	sum = 0;

	for(unsigned int j = i + 1; j < row; j++)
	{
	    for(unsigned int k = 0; k < j; k++)
	    {
		sum += L[i][k] * U[k][j];
	    }
	    U[i][j] = (*lhsMatrix)[i][j] - sum;
	    sum = 0;
	}

	for(unsigned int j = i + 1; j < row; j++)
	{
	    for(unsigned int k = 0; k < j; k++)
	    {
		sum += L[j][k] * U[k][i];
	    }

	    if(!U[i][i])
		throw runtime_error("Cannot solve: Try pivoting or singular matrix\n");

	    L[j][i] = ((*lhsMatrix)[j][i] - sum) / U[i][i];
	    sum = 0;
	}
    }

    luDecomposition->LMatrix = new Matrix(L);
    luDecomposition->UMatrix = new Matrix(U);
} 


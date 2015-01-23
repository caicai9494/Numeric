#include "Matrix.h"

Matrix::Matrix(unsigned int r, unsigned int c):row(r), col(c)
{
    for(unsigned int i = 0; i < r; i++)
        matrixVector.push_back(new Vector(c));
}

Matrix::Matrix(const Matrix &m)
{
    if(&m != NULL)
    {
        row = m.getRow();
        col = m.getCol();

	for(unsigned int i = 0; i < row; i++)
	    matrixVector.push_back(new Vector(m[i]));
    }
}

Matrix::~Matrix()
{
    for(unsigned int i = 0; i < row; i++)
	delete matrixVector.at(i);
}

const Vector& Matrix::operator[](unsigned int r)const 
{
    return *(matrixVector[r]);
}

Vector& Matrix::operator[](unsigned int r)
{
    return *(matrixVector[r]);
}

ostream& operator << (ostream& stream, const Matrix& m)
{
    for(unsigned int i = 0; i < m.row; i++)
    {
	stream << m[i];
	stream << endl;
    }
    stream << endl;
    return stream;
}

Matrix& Matrix::operator= (const Matrix &m)
{
    if(this == &m)
	return *this;
    else
    {
	for(unsigned int i = 0; i < row; i++)
	    delete matrixVector.at(i);
	matrixVector.clear();

        row = m.getRow();
        col = m.getCol();

	for(unsigned int i = 0; i < row; i++)
	    matrixVector.push_back(new Vector(m[i]));
	return *this;
    }
}

Matrix& Matrix::transpose()
{
    MatrixVector newMatrix;

    unsigned int new_row = col;
    unsigned int new_col = row;

    for(unsigned int i = 0; i < new_row; i++)
	newMatrix.push_back(new Vector(new_col));

    for(unsigned int i = 0; i < new_row; i++)
    {
	for(unsigned int j = 0; j < new_col; j++)
	{
	    (*newMatrix.at(i))[j] = (*matrixVector.at(j))[i];
	}
    }

    for(unsigned int i = 0; i < row; i++)
	delete matrixVector.at(i);
    matrixVector.clear();

    row = new_row;
    col = new_col;

    matrixVector = newMatrix;

    return *this;
}

unsigned int Matrix::getRow() const
{
    return row;
}
unsigned int Matrix::getCol() const
{
    return col;
}

Matrix Matrix::operator+ (const Matrix &m)
{
    assert(col == m.getCol() && row == m.getRow());

    Matrix temp(*this);
    
    for(unsigned int r = 0; r < row; r++)
    {
	for(unsigned int c = 0; c < col; c++)
	{
	    temp[r][c] += m[r][c];
	}
    }

    return temp;
}
Matrix Matrix::operator- (const Matrix &m)
{
    assert(col == m.getCol() && row == m.getRow());

    Matrix temp(*this);
    
    for(unsigned int r = 0; r < row; r++)
    {
	for(unsigned int c = 0; c < col; c++)
	{
	    temp[r][c] -= m[r][c];
	}
    }

    return temp;
}

Matrix Matrix::operator* (const Matrix &m)
{
    assert(row == m.getCol());

    Matrix copy_m(m);
    copy_m.transpose();

    Matrix result = Matrix::zeros(m.getCol(), row);


    for(unsigned int r = 0; r < row; r++)
    {
	for(unsigned int c = 0; c < m.getCol(); c++)
	{
	    result[r][c] += (*this)[r].dot(copy_m[c]);
	}
    }

    return result;
}

Matrix Matrix::operator* (const double &num)
{
    Matrix temp(*this);
    
    for(unsigned int r = 0; r < row; r++)
    {
	for(unsigned int c = 0; c < col; c++)
	{
	    temp[r][c] *= num;
	}
    }

    return temp;
}
    
Vector Matrix::operator* (const Vector &v)
{
    assert(v.getIsRowVector() == false && col == v.getDim());

    Vector v2 = Vector::zeros(v.getDim());
    for(unsigned int r = 0; r < row; r++)
    {
	for(unsigned int c = 0; c < col; c++)
	{
	    v2[r] += v[r] * (*this)[r][c];
	}
    }

    v2.transpose();
    return v2;
}
bool Matrix::operator== (const Matrix &m)
{
    if(row != m.getRow() || col != m.getCol())
	return false;

    for(unsigned r = 0; r < row; r++)
    {
	if((*this)[r] != m[r])
	    return false;
    }

    return true;
}

bool Matrix::operator!= (const Matrix &m)
{
    return !((*this) == m);
}

Matrix Matrix::zeros(unsigned int r, unsigned int c)
{
    assert(r > 0 && c > 0);

    Matrix temp(r, c);

    for(unsigned int i = 0; i < r; i++)
    {
	for(unsigned int j = 0; j < c; j++)
	{
	    temp[i][j] = 0;
	}
    }

    return temp;
}

Matrix Matrix::identity(unsigned int r)
{
    assert(r > 0);

    Matrix temp = Matrix::zeros(r, r);

    for(unsigned int i = 0; i < r; i++)
	temp[i][i] = 1;

    return temp;
}
bool Matrix::isUpperTriangle()
{
    if(row != col)
	return false;

    for(unsigned int r = 0; r < row; r++)
    {
        for(unsigned int c = 0; c < r; c++)
	{
	    if((*this)[r][c] != 0)
		return false;
	}
    }

    return true;
}
bool Matrix::isLowerTriangle()
{
    if(row != col)
	return false;

    for(unsigned int r = 0; r < row; r++)
    {
        for(unsigned int c = r + 1; c < col; c++)
	{
	    if((*this)[r][c] != 0)
		return false;
	}
    }

    return true;
}
bool Matrix::isDiagonal()
{
    return isLowerTriangle() && isUpperTriangle();
}
bool Matrix::isSymmetric()
{
    if(row != col)
	return false;

    for(unsigned int r = 0; r < row; r++)
    {
        for(unsigned int c = 0; c <= r; c++)
	{
	    if((*this)[r][c] != (*this)[c][r])
		return false;
	}
    }
    return true;
}

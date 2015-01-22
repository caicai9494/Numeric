#include "Matrix.h"

bool Matrix::getIsTransposed()
{
    return isTransposed;
}

Matrix::Matrix(unsigned int r, unsigned int c):row(r), col(c)
{
    for(unsigned int i = 0; i < r; i++)
        matrixVector.push_back(new Vector(c));
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
	    (*this)[i][j] = (*matrixVector.at(j))[i];
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

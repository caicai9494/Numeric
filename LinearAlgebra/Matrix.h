#ifndef _MATRIX_H
#define _MATRIX_H

#include <vector>
#include "Vector.h"

using namespace std;

class Matrix
{
    typedef vector<Vector*>MatrixVector;
    public:
	Matrix(unsigned int r, unsigned int c);
	Matrix(const Matrix &m);
	const Vector& operator[](unsigned int r) const;
	Vector& operator[](unsigned int r);
	Matrix operator+ (const Matrix &m);
	Matrix operator- (const Matrix &m);
	Matrix operator* (const Matrix &m);
	Matrix operator* (const double &num);
	Matrix& operator= (const Matrix &m);

	friend ostream& operator << (ostream& stream, const Matrix& m);

	Matrix& transpose();
	~Matrix();

	unsigned int getRow() const;
	unsigned int getCol() const;

    private:
	MatrixVector matrixVector;
	unsigned int row;
	unsigned int col;
};
#endif

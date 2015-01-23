#ifndef _MATRIX_H
#define _MATRIX_H

#include <vector>
#include <iostream>
#include "Vector.h"

using namespace std;

class Vector;

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
	//not yet done
	Matrix operator* (const Matrix &m);
	Matrix operator* (const double &num);
	Vector operator* (const Vector &v);
	Matrix& operator= (const Matrix &m);
	bool operator== (const Matrix &m);
	bool operator!= (const Matrix &m);

	friend ostream& operator << (ostream& stream, const Matrix& m);

	Matrix& transpose();
	~Matrix();

	unsigned int getRow() const;
	unsigned int getCol() const;

	static Matrix zeros(unsigned int r, unsigned int c);
	static Matrix identity(unsigned int r);

	bool isUpperTriangle();
	bool isLowerTriangle();
	bool isDiagonal();
	bool isSymmetric();

    private:
	MatrixVector matrixVector;
	unsigned int row;
	unsigned int col;
};
#endif

#ifndef _MATRIX_H
#define _MATRIX_H

#include <vector>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include "Vector.h"
#include "../common/type.h"

using namespace std;

class Vector;
class LUDecomposition;

class Matrix
{
    typedef vector<Vector*>MatrixVector;
    public:
	Matrix(unsigned int r, unsigned int c);
	Matrix(const Matrix &m);

	virtual ~Matrix();

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

	Matrix transpose() const;
	//use gauss-jordan method
	Matrix inverse();

	unsigned int getRow() const;
	unsigned int getCol() const;
	unsigned int getR();

	static Matrix zeros(unsigned int r, unsigned int c);
	static Matrix identity(unsigned int r);
	//throw runtime_error if v invalid
	static Matrix vandermonde(const Vector &v);

	bool isUpperTriangle();
	bool isLowerTriangle();
	bool isDiagonal();
	bool isSymmetric();
	bool isSquare();

	void swapRow(unsigned int i, unsigned int j);
	void swapCol(unsigned int i, unsigned int j);

    private:
	MatrixVector matrixVector;
	unsigned int row;
	unsigned int col;
};

class LUDecomposition
{
    public:
	LUDecomposition(unsigned int i);
	~LUDecomposition();

	Matrix *LMatrix;
	Matrix *UMatrix;
	unsigned int *permutation;
    private:

	LUDecomposition(const LUDecomposition &lu) {}
	LUDecomposition& operator= (const LUDecomposition &lu);
};

#endif

#ifndef _MATRIX_H
#define _MATRIX_H
#include "Vector.h"
#include <vector>
class Matrix
{
    typedef vector<Vector*>MatrixVector;
    public:
	Matrix(unsigned int r, unsigned int c);
	const Vector& operator[](unsigned int r) const;
	Vector& operator[](unsigned int r);

	friend ostream& operator << (ostream& stream, const Matrix& m);

	bool getIsTransposed();
	Matrix& transpose();
	~Matrix();

    private:
	MatrixVector matrixVector;
	unsigned int row;
	unsigned int col;

	bool isTransposed;
    

};
#endif

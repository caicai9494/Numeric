#ifndef _VECTOR_H
#define _VECTOR_H
#include <cassert>
#include <cstring>
#include <iostream>
#include <iomanip>
#include "Matrix.h"

using namespace std;

class Matrix;

class Vector
{
    public:
	explicit Vector(unsigned int i);
	Vector(const Vector &v);

	Vector& transpose();

	bool getIsRowVector() const;
	double dot(const Vector &v);
	unsigned int getDim() const;

	const double operator[](unsigned int i) const;
	double &operator[](unsigned int i);
	Vector& operator = (const Vector &v);
	//shall be product...
	//can return a matrix or a double
	//To simplify it can only deal with
	//col v * row v
	Matrix operator* (const Vector &v);
	//col v * matrix m
	Matrix operator* (const Matrix &m);
	//Matrix operator* (const Vector &v);
	Vector operator+ (const Vector &v);
	Vector operator- (const Vector &v);
	bool operator== (const Vector &v) const;
	bool operator!= (const Vector &v) const;


	friend Vector operator*(Vector lhs, const double num);
	friend Vector operator*(const double num, Vector rhs);
	friend ostream& operator<<(ostream &stream, const Vector &v);

	static Vector zeros(unsigned int r);

	~Vector();

    private:
	double *vector;
	unsigned int dim;
	bool isRowVector;
};
#endif

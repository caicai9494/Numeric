#include "Vector.h"

namespace Numeric
{

    Vector::Vector(unsigned int i)
    {
	assert(i > 0);

	dim = i;
	vector = new double[i];
	isRowVector = true;
    }

    Vector::Vector(const Vector &v)
    {
	if(&v != NULL)
	{
	    unsigned int v_dim = v.getDim();

	    vector = new double[v_dim];
	    dim = v_dim;
	    isRowVector = v.getIsRowVector();
	    for(unsigned int i = 0; i < v_dim; i++)
	    {
		vector[i] = v[i];
	    }
	}
	
    }

    Vector::Vector()
    {
	dim = 0;
	isRowVector = true;
	vector = NULL;
    }

    Vector::~Vector()
    {
	delete []vector;
    }

    bool Vector::getIsRowVector() const
    {
	return isRowVector;
    }

    Vector& Vector::operator = (const Vector &v)
    {

	if(this != &v)
	{
	    delete []vector;
	    unsigned int v_dim = v.getDim();
	    isRowVector = v.getIsRowVector();

	    vector = new double[v_dim];
	    for(unsigned int i = 0; i < v_dim; i++)
	    {
		vector[i] = v[i];
	    }
	}

	return *this;
    }
    const double Vector::operator[](unsigned int i) const
    {
	assert(i < dim && i >= 0);

	return vector[i];
    }

    double &Vector::operator[](unsigned int i)
    {
	assert(i < dim && i >= 0);

	return vector[i];
    }

    double Vector::dot(const Vector &v)
    {
	unsigned int len = v.getDim();
	assert(len == this->dim);

	double product = 0;

	for(unsigned int i = 0; i < len; i++)
	{
	    product += v[i] * vector[i];
	}

	return product;
    }

    Matrix Vector::operator*(const Vector &v)
    {
	unsigned int len = v.getDim();
	assert(len == this->dim && !isRowVector && v.getIsRowVector());

	Matrix m(len, len);

	for(unsigned int i = 0; i < len; i++)
	{
	    for(unsigned int j = 0; j < len; j++)
	    {
		m[i][j] = vector[i] * v[j];
	    }
	}
	return m;
    }
    Matrix Vector::operator* (const Matrix &m)
    {
	assert(dim == m.getRow() && isRowVector);

	Matrix m2(m);

	for(unsigned int r = 0; r < m.getRow(); r++)
	{
	    for(unsigned int c = 0; c < m.getRow(); c++)
	    {
		m2[r][c] *= vector[r];
	    }
	}

	return m2;
    }

    Vector Vector::operator+ (const Vector &v)
    {
	unsigned int v_dim = v.getDim();
	assert(isRowVector == v.getIsRowVector() && v_dim == dim);

	Vector temp(v_dim);
	for(unsigned int i = 0; i < dim; i++)
	{
	    temp[i] = this->vector[i] + v[i];
	}

	return temp;
    }

    Vector Vector::operator- (const Vector &v)
    {
	unsigned int v_dim = v.getDim();
	assert(isRowVector == v.getIsRowVector() && v_dim == dim);

	Vector temp(v_dim);
	for(unsigned int i = 0; i < dim; i++)
	{
	    temp[i] = this->vector[i] - v[i];
	}

	return temp;
    }

    bool Vector::operator!= (const Vector &v) const
    {
	return !((*this) == v);
    }
    bool Vector::operator== (const Vector &v) const
    {
	unsigned int v_dim = v.getDim();
	if(isRowVector != v.getIsRowVector() || v_dim != dim)
	    return false;

	for(unsigned i = 0; i < v_dim; i++)
	{
	    if(vector[i] != v[i])
		return false;
	}
	return true;
    }

    Vector operator*(Vector lhs, const double num)
    {
	Vector temp(lhs);
	unsigned int len = lhs.getDim();

	for(unsigned int i = 0; i < len; i++)
	    temp[i] *= num;

	return temp;
    }

    Vector operator*(const double num, Vector rhs)
    {
	Vector temp(rhs);
	unsigned int len = rhs.getDim();

	for(unsigned int i = 0; i < len; i++)
	    temp[i] *= num;

	return temp;
    }

    ostream& operator<<(ostream &stream, const Vector &v)
    {
	if(v.isRowVector)
	{
	    unsigned int dim = v.getDim();
	    for(unsigned int i = 0; i < dim; i++)
	    {
		if(abs(v[i]) < DOUBLE_IGNORANCE)
		    stream << setfill(' ') << setw(9) << 0.0 << "   ";
		else
		    stream << setfill(' ') << setw(9) <<  v[i] << "   ";
	    }
	    return stream;
	}
	else
	{
	    unsigned int dim = v.getDim();
	    for(unsigned int i = 0; i < dim; i++)
	    {
		if(abs(v[i]) < DOUBLE_IGNORANCE)
		    stream << setfill(' ') << setw(9) << 0.0 << endl;
		else 
		    stream << setfill(' ') << setw(9) << v[i] << endl;
		stream << endl;
	    }
	    return stream;
	}
    }
    unsigned int Vector::getDim() const
    {
	return dim;
    }

    Vector& Vector::transpose()
    {
	isRowVector = !isRowVector;
	return *this;
    }

    Vector Vector::zeros(unsigned int r)
    {
	Vector v(r);

	for(unsigned int i = 0; i < r; i++)
	    v[i] = 0;

	return v;
    }
    void Vector::swap(unsigned int i, unsigned int j)
    {
	assert(i >= 0 && j >= 0 && i < dim && j < dim);

	util::swap(vector[i], vector[j]);
    }
}


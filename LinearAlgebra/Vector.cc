#include "Vector.h"

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
    else
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

double Vector::operator*(const Vector &v)
{
    unsigned int len = v.getDim();
    assert(len == this->dim);

    //if(isRowVector == true && v.getIsRowVector() == false)

    double product = 0;

    for(unsigned int i = 0; i < len; i++)
    {
	product += v[i] * vector[i];
    }

    return product;
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
    assert(isRowVector == v.getIsRowVector() && v_dim == dim);

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
	    stream << v[i] << " ";
        return stream;
    }
    else
    {
	unsigned int dim = v.getDim();
        for(unsigned int i = 0; i < dim; i++)
	    stream << v[i] << endl;
	return stream;
    }
}
unsigned int Vector::getDim() const
{
    return dim;
}

void Vector::print()
{
    if(isRowVector)
    {
        for(unsigned int i = 0; i < dim; i++)
	    cout << vector[i] << " ";
        cout << endl;
    }
    else
    {
        for(unsigned int i = 0; i < dim; i++)
	    cout << vector[i] << endl;
    }
}
Vector& Vector::transpose()
{
    isRowVector = !isRowVector;
    return *this;
}

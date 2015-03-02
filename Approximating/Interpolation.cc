#include "Interpolation.h"


namespace Numeric
{

    ostream& operator<< (ostream& stream, const Point2D& p)
    {
	stream << "Point2D : ( ";
	stream << setw(4) << setfill(' ') << p.x;
	stream << ", ";
	stream << setw(4) << setfill(' ') << p.y;
	stream << " ) \n";

	return stream;
    }

    Point2D::Point2D(double _x, double _y):x(_x), y(_y){}

    bool Point2D::operator< (const Point2D& p)
    {
	return (x < p.x) ? -1 : (x == p.x) ? 0 : 1;
    }

    Interpolation::Interpolation(){}
    Interpolation::~Interpolation(){}

    void Interpolation::addPoint(Point2D p){}
    void Interpolation::addPointArray(vector<Point2D> pVec){}
    void Interpolation::deletePoint(Point2D p){}
    double Interpolation::interpolate(double x){return 0;}
    unsigned int Interpolation::pointSize()const {return 0;}

    NewtonInterpolation::NewtonInterpolation():Interpolation()
    {
    }
    NewtonInterpolation::~NewtonInterpolation()
    {
    }
    NewtonInterpolation& NewtonInterpolation::operator= (const NewtonInterpolation&) {return *this;}

    void NewtonInterpolation::addPoint(Point2D p)
    {
	typedef vector<double>::iterator IT;

	if(coeffArray.empty())
	    coeffArray.push_back(p.y);
	else
	{
	    double coeff;
	    double diff = 1;
	    double pk_1 = interpolate(p.x);

	    for(IT it = xArray.begin(); it != xArray.end(); it++)
		diff *= (p.x - *it); 

	    coeff = (p.y - pk_1) / diff;
	    coeffArray.push_back(coeff);
	}

	xArray.push_back(p.x);
    }

    double NewtonInterpolation::interpolate(double x)
    {
	if(coeffArray.empty())
	    throw runtime_error("Cannot interpolate: non points inputed\n");

	double uk = *(coeffArray.end() - 1);

	for(int i = coeffArray.size() - 2; i >= 0; i--)
	    uk = (x - xArray[i]) * uk + coeffArray[i];

	return uk;
    }
    void NewtonInterpolation::addPointArray(vector<Point2D> pVec)
    {
	vector<Point2D>::iterator it;
	for(it = pVec.begin(); it != pVec.end(); it++)
	    addPoint(*it);
    }

    unsigned int NewtonInterpolation::pointSize()const
    {
	return coeffArray.size();
    }

    ostream& operator<< (ostream& stream, const NewtonInterpolation& nitrp)
    {
	stream << "NewtonInterpolation\n";
	stream << "f(x) = \n\n";
	for(unsigned int i = 0; i < nitrp.pointSize(); i++)
	{
	    stream << setw(5) <<  setfill(' ') << nitrp.coeffArray[i] << " * ";
	    //stream << nitrp.coeffArray[i];
	    for(unsigned int j = 0; j < i; j++)
	    {
		double num = nitrp.xArray[j];
		if(num > 0)
		    stream << " ( x - " << num << " ) ";
		else if(num < 0)
		    stream << " ( x + " << -num << " ) ";
		else 
		    stream << " ( x" << " ) ";
	    }
	    if(i != nitrp.pointSize() - 1)
		stream << " + ";
	    stream << endl;
	    stream << endl;
	}
	return stream;
    }

    LagrangeInterpolation::LagrangeInterpolation():Interpolation(){}
    LagrangeInterpolation::~LagrangeInterpolation(){}
    LagrangeInterpolation& LagrangeInterpolation::operator= (const LagrangeInterpolation&) {return *this;}
    unsigned int LagrangeInterpolation::pointSize() const
    {
	return pVector.size();
    }

    void LagrangeInterpolation::addPoint(Point2D p)
    {
	pVector.push_back(p);
	//denominators has to be recalculated
	denominatorVector.clear();
    }

    void LagrangeInterpolation::addPointArray(vector<Point2D> pVec)
    {
	denominatorVector.clear();
	pVector.insert(pVector.end(), pVec.begin(), pVec.end());
    }

    void LagrangeInterpolation::setupDenominator()
    {
	double deno;
	for(unsigned int i = 0; i < pointSize(); i++)
	{
	    deno = 1;
	    for(unsigned int j = 0; j < pointSize(); j++)
	    {
		if(i != j)
		{
		    double diff = pVector[i].x - pVector[j].x;
		    if(diff == 0)
			throw(runtime_error("Cannot Interpolate: divide by zero\n"));
		    deno *= (pVector[i].x - pVector[j].x); 
		}
	    }
	    denominatorVector.push_back(deno);
	}
    }

    double LagrangeInterpolation::interpolate(double x){
	if(pVector.empty())
	    throw runtime_error("Cannot interpolate: non points inputed\n");
	if(denominatorVector.empty())
	    setupDenominator();

	double sum, partsum;
	sum = 0;

	for(unsigned int i = 0; i < pointSize(); i++)
	{
	    partsum = 1;
	    for(unsigned int j = 0; j < pointSize(); j++)
	    {
		if(j != i)
		    partsum *= (x - pVector[j].x);
	    }
	    sum += pVector[i].y * partsum / denominatorVector[i];
	}

	return sum;
    }


    ostream& operator<< (ostream& stream, const LagrangeInterpolation& litrp)
    {
	stream << "LagrangeInterpolation\n";
	stream << "f(x) = \n\n";
	for(unsigned int i = 0; i < litrp.pointSize(); i++)
	{
	    stream << setw(5) <<  setfill(' ') << litrp.pVector[i].y << " * ";
	    //stream << nitrp.coeffArray[i];
	    for(unsigned int j = 0; j < litrp.pointSize(); j++)
	    {
		if(i != j)
		{
		    double num = litrp.pVector[j].x;
		    if(num > 0)
			stream << " ( x - " << num << " ) ";
		    else if(num < 0)
			stream << " ( x + " << -num << " ) ";
		    else 
			stream << " ( x" << " ) ";
		}
	    }
	    stream << endl;
	    for(unsigned int k = 0; k < litrp.pointSize(); k++)
		stream << "---------------";
	    stream << " + ";
	    stream << endl;

	    for(unsigned int j = 0; j < litrp.pointSize(); j++)
	    {
		if(i != j)
		{
		    double num = litrp.pVector[j].x;
		    if(num > 0)
			stream << " ( " << litrp.pVector[i].x << " - " << num << " ) ";
		    else if(num < 0)
			stream << " ( " << litrp.pVector[i].x << " + " << -num << " ) ";
		    else 
			stream << " ( " << litrp.pVector[i].x << " ) ";
		}
	    }

	    stream << endl;
	    stream << endl;
	}
	return stream;
    }

}

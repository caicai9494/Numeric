#ifndef _INTERPOLATION_H
#define _INTERPOLATION_H
#include <string>
#include <vector>
#include <iomanip>
#include <iostream>
#include <stdexcept>

using namespace std;
namespace Numeric
{

    struct Point2D
    {
	double x;
	double y;
	Point2D(double _x, double _y);
	bool operator< (const Point2D& p);
    };

    ostream& operator<< (ostream& stream, const Point2D& p);


    class Interpolation
    {
	public:
	    Interpolation();
	    virtual ~Interpolation() = 0;
	    virtual void addPoint(Point2D p);
	    virtual void addPointArray(vector<Point2D> pVec);
	    virtual void deletePoint(Point2D p);

	    virtual double interpolate(double x);
	    virtual unsigned int pointSize() const;
    };

    class LagrangeInterpolation: public Interpolation
    {
	typedef vector<Point2D> PVector;
	typedef vector<double> dVector;
	public:
	    LagrangeInterpolation();
	    ~LagrangeInterpolation();

	    void addPoint(Point2D p);
	    void addPointArray(vector<Point2D> pVec);
	    unsigned int pointSize() const;

	    //throw runtime_error if cannot interpolate at x
	    double interpolate(double x);
	    friend ostream& operator<< (ostream& stream, const LagrangeInterpolation& litrp);
	private:
	    LagrangeInterpolation& operator= (const LagrangeInterpolation&);
	    LagrangeInterpolation(const LagrangeInterpolation&) {}

	    PVector pVector;
	    dVector denominatorVector;
	    //throw runtime_error if points with same x value is inputed
	    void setupDenominator();
    };

    class NewtonInterpolation: public Interpolation
    {
	typedef vector<double> dVector;
	typedef vector<double>::reverse_iterator RIT;
	public:
	    NewtonInterpolation();
	    ~NewtonInterpolation();

	    void addPoint(Point2D p);
	    void addPointArray(vector<Point2D> pVec);
	    unsigned int pointSize() const;

	    //throw runtime_error if not points inputed
	    double interpolate(double x);

	    friend ostream& operator<< (ostream& stream, const NewtonInterpolation& nitrp);
	private:
	    dVector coeffArray;
	    dVector xArray;

	    NewtonInterpolation& operator= (const NewtonInterpolation&);
	    NewtonInterpolation(const NewtonInterpolation&) {}
    };

}
#endif

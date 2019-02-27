#pragma once
#include "Point.h"

class Vector {
private:
	double x;
	double y;
public:
	Vector();
	Vector( double, double );
	Vector( const Point&, const Point& );
	Vector( const Vector& );

	Vector& operator=( const Vector& );

	friend double ScalarProduct( const Vector&, const Vector& );
	friend double VectorProduct( const Vector&, const Vector& );

};
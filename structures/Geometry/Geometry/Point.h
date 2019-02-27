#pragma once
#include <cmath>
#include "Shape.h"

class Segment;

class Point : public Shape {
protected:
	double x;
	double y;
public:
	Point();
	Point( double, double );
	Point( const Point& );
	
	Point& operator=( const Point& );

	bool operator==( const Point& ) const;

	double GetX() const;
	double GetY() const;

	void Move( double, double );
	bool IsPointIn( const Point& ) const;
	Intersection Intersect( const Segment& ) const;

	bool isPointBetween( const Point&, const Point& ) const;

	friend double Distance( const Point&, const Point& );
	double DistanceToStraight( double, double, double ) const;
	double ModulToStraight( double, double, double ) const;

};
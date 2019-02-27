#pragma once
#include "Shape.h"
#include "Point.h"
#include "Segment.h"

class Circle : public Shape {
protected:
	Point p;
	double r;
public:
	Circle();
	Circle( const Point&, double );
	Circle( const Circle& );

	Circle& operator=( const Circle& );
	bool operator==( const Circle& ) const;

	Point GetCenter() const;
	double GetRadius() const;

	void Move( double, double );
	bool IsPointIn( const Point& ) const;
	Intersection Intersect( const Segment& ) const;
};
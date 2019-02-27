#pragma once
#include <cmath>
#include "Shape.h"
#include "Point.h"

class Segment : public Shape {
protected:
	Point p1;
	Point p2;
public:
	Segment();
	Segment( const Point&, const Point& );
	Segment( const Segment& );

	Segment& operator=( const Segment& );

	bool operator==( const Segment& ) const;
	
	Point GetP1() const;
	Point GetP2() const;

	void SetP1( const Point& );
	void SetP2( const Point& );

	void Move( double, double );
	bool IsPointIn( const Point& ) const;
	Intersection Intersect( const Segment& ) const;

	double DistanceToPoint( const Point& ) const;
	double ModuleToPoint( const Point& ) const;

};
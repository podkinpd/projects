#pragma once
#include <cmath>
#include "Shape.h"
#include "Point.h"
#include "Segment.h"

class Functor {
private:
	Point o;
public:
	Functor();
	Functor( const Point& );
	bool operator()( const Point&, const Point& );
};

class Polygon : public Shape {
protected:
	CArray<Point> buf;
public:
	Polygon();
	Polygon( const CArray<Point>& );
	Polygon( const Polygon& );

	CArray<Point>& GetLinkToBuf();
	
	Polygon& operator=( const Polygon& );
	bool operator==( const Polygon&) const;
	Point operator[]( const size_t ) const;
	void Move( double, double );
	bool IsPointIn( const Point& ) const;
	Intersection Intersect( const Segment& ) const; 

	Polygon ConvexHull() const;
};
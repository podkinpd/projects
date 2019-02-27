#pragma once
#include "CArray.h"

class Point;
class Segment;
class Intersection;

class Shape {
public:
	virtual void Move( double, double ) = 0;
	virtual bool IsPointIn( const Point& ) const = 0;
	virtual Intersection Intersect( const Segment& ) const = 0; 

};

class Intersection {
private:
	CArray<Point> bufOfPoints;
	CArray<Segment> bufOfSegments;
public:
	Intersection();
	Intersection( const Intersection& );

	Intersection& operator=( const Intersection& );

	size_t GetNumberOfPoints() const;
	size_t GetNumberOfSegments() const;

	CArray<Point> GetPoints() const;
	CArray<Segment> GetSegments() const;

	CArray<Point>& GetLinkToBufOfPoints();
	CArray<Segment>& GetLinkToBufOfSegments();

	void AddIntersection( const Intersection& );
};
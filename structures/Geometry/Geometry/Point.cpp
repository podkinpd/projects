#include "Point.h"
#include "Segment.h"

Point::Point() : x(0), y(0) {
}

Point::Point( double a, double b ) : x(a), y(b) {
}

Point::Point( const Point& p ) : x(p.x), y(p.y) {
}

Point& Point::operator=( const Point& p ) {
	x = p.x;
	y = p.y;
	return *this;
}

bool Point::operator==( const Point& p ) const {
	double eps = 0.00000001;
	if( fabs( x - p.x ) < eps && fabs( y - p.y ) < eps ) {
		return true;
	}
	else {
		return false;
	}
}

double Point::GetX() const {
	return x;
}

double Point::GetY() const {
	return y;
}

void Point::Move( double dx, double dy ) {
	x += dx;
	y += dy;
}

bool Point::IsPointIn( const Point& p ) const {
	double eps = 0.00000001;
	if( fabs( x - p.x ) < eps && fabs( y - p.y) < eps ) {
		return true;
	}
	else {
		return false;
	}
}

Intersection Point::Intersect( const Segment& s ) const {
	Intersection result;	
	Point p1 = s.GetP1(), p2 = s.GetP2();
/*	if( s.DistanceToPoint( *this ) == 0 ) {
		Intersection result;
		result.GetLinkToBuf().PushBack( *this );
		result.SetIsSegment( true );
	}
	*/
	double eps = 0.00000001;
	double r;
	double x1 = p1.GetX(), y1 = p1.GetY(), x2 = p2.GetX(), y2 = p2.GetY();
	r = this->ModulToStraight( y1 - y2, x2 - x1, x1 * y2 - x2 * y1 );
	if( ( r < eps ) && ( x <= x1 && x >= x2 ) || ( x <= x2 && x >= x1 ) ) {
			result.GetLinkToBufOfPoints().PushBack( *this );
	}
	return result;
}

bool Point::isPointBetween( const Point& p1, const Point& p2 ) const {
	if( ( ( x <= p1.x && x >= p2.x ) || ( x >= p1.x && x <= p2.x ) ) && ( ( y <= p1.y && y >= p2.y ) || ( y >= p1.y && y <= p2.y ) ) ) {
		return true;
	}
	else {
		return false;
	}
}

double Distance( const Point& p1, const Point& p2 ) {
	return sqrt( ( p1.GetX() - p2.GetX() ) * ( p1.GetX() - p2.GetX() ) + ( p1.GetY() - p2.GetY() ) * ( p1.GetY() - p2.GetY() ) );
}

double Point::DistanceToStraight( double a, double b, double c ) const {
	return ( a * x + b * y + c ) / sqrt( a * a + b * b );
}

double Point::ModulToStraight( double a, double b, double c ) const {
	return fabs( this->DistanceToStraight( a, b, c ) );
}
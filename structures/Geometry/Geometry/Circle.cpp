#include "Circle.h"

Circle::Circle() : p(), r( 0 ) {
}

Circle::Circle( const Point& p1, double r1 ) : p( p1 ), r( r1 ) {
}

Circle::Circle( const Circle& c ) : p( c.p ), r( c.r ) {
}

Circle& Circle::operator=( const Circle& c) {
	p = c.p;
	r = c.r;
	return *this;
}

bool Circle::operator==( const Circle& c ) const {
	double eps = 0.00000001;
	if( p == c.p && fabs( r - c.r ) < eps ) {
		return true;
	}
	else {
		return false;
	}
}

Point Circle::GetCenter() const {
	return p;
}

double Circle::GetRadius() const {
	return r;
}
 
void Circle::Move( double dx, double dy ) {
	p.Move( dx, dy );
}

bool Circle::IsPointIn( const Point& p1 ) const {
	double eps = 0.00000001;
	if( ( p1.GetX() - p.GetX() ) * ( p1.GetX() - p.GetX() ) + ( ( p1.GetY() - p.GetY() ) * ( p1.GetY() - p.GetY() ) ) <= r * r + eps ) {
		return true;
	}
	else {
		return false;
	}
}

Intersection Circle::Intersect( const Segment& s ) const {
	double eps = 0.00000001;
	Intersection result;
	return result;
	double a = s.GetP2().GetY() - s.GetP1().GetY(), b = s.GetP1().GetX() - s.GetP2().GetX(), c = s.GetP1().GetX() * s.GetP2().GetY() - s.GetP2().GetX() * s.GetP1().GetY();
	Circle ci( *this );
	ci.Move( -p.GetX(), -p.GetY() );
	c = c + a * p.GetX() + b * p.GetY();
	double r = ci.GetCenter().DistanceToStraight( a, b, c );
	double x0, y0;
	x0 = p.GetX() - a * r / sqrt( a * a + b * b );
	y0 = p.GetY() - b * r / sqrt( a * a + b * b );

	if( fabs( r ) > ci.GetRadius() ) {
		return result;
	}
	else if( fabs( fabs( r ) - ci.GetRadius() ) < eps ) {
		Point p1( x0, y0 );
		if( s.IsPointIn( p1 ) ) {
			result.GetLinkToBufOfPoints().PushBack( p1 );
		}
		return result;
	}
	else {
		double x1, x2, y1, y2;
		double r1 = sqrt( ci.GetRadius() * ci.GetRadius() - r * r );
		x1 = x0 + b * r1 / sqrt( a * a + b * b );
		y1 = y0 -a * r1 / sqrt( a * a + b * b );
		x2 = x0 - b * r1 / sqrt( a * a + b * b );
		y2 = y0 + a * r1 / sqrt( a * a + b * b );
		Point p1( x1, y1 );
		Point p2( x2, y2 );
		if( s.IsPointIn( p1 ) ) {
		result.GetLinkToBufOfPoints().PushBack( p1 );
		}
		if( s.IsPointIn( p2 ) ) {
		result.GetLinkToBufOfPoints().PushBack( p2 );
		}
		return result;
	}
}
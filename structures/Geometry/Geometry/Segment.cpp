#include "Segment.h"
#include <cmath>
#include <iostream>

Segment::Segment() : p1(), p2() {
}

Segment::Segment( const Point& a, const Point& b ) : p1(a), p2(b) {
}

Segment::Segment( const Segment& s ) : p1(s.p1), p2(s.p2) {
}

Segment& Segment::operator=( const Segment& s ) {
	p1 = s.p1;
	p2 = s.p2;
	return *this;
}

bool Segment::operator==( const Segment& s ) const {
	if( p1 == s.p1 && p2 == s.p2 ) {
		return true;
	}
	else {
		return false;
	}
}

Point Segment::GetP1() const {
	return p1;
}

Point Segment::GetP2() const {
	return p2;
}

void Segment::SetP1( const Point& p ) {
	p1 = p;
}

void Segment::SetP2( const Point& p ) {
	p2 = p;
}

void Segment::Move( double dx, double dy ) {
	p1.Move( dx, dy );
	p2.Move( dx, dy );
}

bool Segment::IsPointIn( const Point& p ) const {
	double eps = 0.0000000001;
	if( p.GetX() < std::min( p1.GetX(), p2.GetX() ) || p.GetX() > std::max( p1.GetX(), p2.GetX() ) || p.GetY() < std::min( p1.GetY(), p2.GetY() ) || p.GetY() > std::max( p1.GetY(), p2.GetY() ) ) {
		return false;
	}
	if( fabs( this->DistanceToPoint( p ) ) < eps ) {
		return true;
	}
	else {
		return false;
	}
}

Intersection Segment::Intersect( const Segment& s ) const {
	Intersection result;
	if( s.GetP1() == s.GetP2() ) {
		if( this->IsPointIn( s.GetP1() ) ) {
			result.GetLinkToBufOfPoints().PushBack( s.GetP1() );
			return result;
		}
		else {
			return result;
		}
	}
	else if( p1 == p2 ) {
		if( s.IsPointIn( p1 ) ) {
			result.GetLinkToBufOfPoints().PushBack( p1 );
			return result;
		}
		else {
			return result;
		}
	}
	double eps = 0.00000001;
	double a1, b1, c1, a2, b2, c2;
	a1 = p2.GetY() - p1.GetY();
	a2 = s.GetP2().GetY() - s.GetP1().GetY();
	b1 = p1.GetX() - p2.GetX();
	b2 = s.GetP1().GetX() - s.GetP2().GetX();
	c1 = - p1.GetX() * p2.GetY() + p2.GetX() * p1.GetY();
	c2 = - s.GetP1().GetX() * s.GetP2().GetY() + s.GetP2().GetX() * s.GetP1().GetY();
	bool flag = false;
	if( fabs( a2 ) < eps ) {
		if( fabs( a1 ) < eps ) {
			if( fabs( b1 ) < eps ) {
				if( fabs( b2 ) < eps ) {
					if( p1 == s.GetP1() ) {
						result.GetLinkToBufOfPoints().PushBack( p1 );
						return result;
					}
					else {
						return result;
					}
				}
				else {
					if( s.IsPointIn( p1 ) ) {
						result.GetLinkToBufOfPoints().PushBack( p1 );
						return result;
					}
					else {
						return result;
					}
				}
			}
			else if( fabs( b2 ) < eps ) {
				if( this->IsPointIn( s.GetP1() ) ) {
					result.GetLinkToBufOfPoints().PushBack( s.GetP1() );
					return result;
				}
				else {
					return result;
				}
			}
			else {
				if( fabs( c1 * b2 / b1 - c2 ) < eps ) {
					flag = true;
				}
			}
		}
		else {
			flag = false;
		}
	}
	else if( fabs( a1 ) < eps ) {
		flag = false;
	}
	else {
		b2 *= ( a1 / a2 );
		c2 *= ( a1 / a2 );
		a2 = a1;
		if( fabs( b1 - b2 ) < eps && fabs( c1 - c2 ) < eps ) {
			flag = true;
		}
	}
	if( flag ) {
		if( p1.isPointBetween( s.GetP1(), s.GetP2() ) ) {
			if( p2.isPointBetween( s.GetP1(), s.GetP2() ) ) {
				Segment s1( p1, p2 );
				result.GetLinkToBufOfSegments().PushBack( s1 );
				return result;
			}
			else if( p1 == s.GetP1() || p1 == s.GetP2() ) {
				result.GetLinkToBufOfPoints().PushBack( p1 );
				return result;
			}
			else if( s.GetP1().isPointBetween( p1, p2 ) ) {
				Segment s1( p1, s.GetP1() );
				result.GetLinkToBufOfSegments().PushBack( s1 );
				return result;
			}
			else {
				Segment s1( p1, s.GetP2() );
				result.GetLinkToBufOfSegments().PushBack( s1 );
				return result;
			}
		}
		else if( p2.isPointBetween( s.GetP1(), s.GetP2() ) ) {
			if( s.GetP1().isPointBetween( p1, p2 ) ) {
				Segment s1( p2, s.GetP1() );
				result.GetLinkToBufOfSegments().PushBack( s1 );
				return result;
			}
			else if( s.GetP2().isPointBetween( p1, p2 ) ) {
				Segment s1( p2, s.GetP2() );
				result.GetLinkToBufOfSegments().PushBack( s1 );
				return result;
			}
		}
		else if( s.GetP1().isPointBetween( p1, p2 ) && s.GetP2().isPointBetween( p1, p2 ) ) {
			result.GetLinkToBufOfSegments().PushBack( s );
			return result;
		}
		else {
			return result;
		}
	}
	else {
		double x, y;
		x = ( c2 * b1 - c1 * b2 ) / ( a1 * b2 - a2 * b1 );
		y = ( a2 * c1 - a1 * c2 ) / ( a1 * b2 - a2 * b1 );
		Point p( x, y );
		//std::cout << x << ' ' << y;
		if( s.IsPointIn( p ) && this->IsPointIn( p ) ) {
			result.GetLinkToBufOfPoints().PushBack( p );
		}
		return result;
	}
}

double Segment::DistanceToPoint( const Point& p ) const {
	double eps = 0.00000001;
	double d1 = Distance( p1, p ), d2 = Distance( p2, p ), d;
	double x1 = p1.GetX(), y1 = p1.GetY(), x2 = p2.GetX(), y2 = p2.GetY(), x = p.GetX(), y = p.GetY();
	d = p.ModulToStraight( y1 - y2, x2 - x1, x1 * y2 - x2 * y1 );
	if( fabs( d ) < eps ) {
		if( ( x <= x1 && x >= x2 ) || ( x <= x2 && x >= x1 ) ) {
			return 0;
		}
		else {
			return std::min( d1, d2 );
		}
	}
	else {
		return std::min( d1, std::min( d2, d ) );
	}
}

double Segment::ModuleToPoint( const Point& p ) const {
	return fabs( this->DistanceToPoint( p ) );
}
#include "Polygon.h"
#include "Vector.h"
#include <algorithm>
#include <iostream>

Polygon::Polygon() :buf() {
}

Polygon::Polygon( const CArray<Point>& arr ) : buf( arr ){
}

Polygon::Polygon( const Polygon& pol ) : buf( pol.buf ) {
}

CArray<Point>& Polygon::GetLinkToBuf() {
	return buf;
}

Polygon& Polygon::operator=( const Polygon& pol ) {
	if( this != &pol ) {
		buf = pol.buf;
	}
	return *this;
}

bool Polygon::operator==( const Polygon& pol ) const {
	if( buf.GetSize() != pol.buf.GetSize() ) {
		return false;
	}
	else {
		for( size_t i = 0; i < buf.GetSize(); i++ ) {
			if( !( buf[i] == pol.buf[i] ) ) {
				return false;
			}
		}
		return true;
	}
}

Point Polygon::operator[]( const size_t index ) const {
	return buf[index];
}

void Polygon::Move( const double dx, const double dy ) {
	for( size_t i = 0; i < buf.GetSize(); i++ ) {
		buf[i].Move( dx, dy );
	}
}

bool Polygon::IsPointIn( const Point& p ) const {
	double eps = 0.00000001;
	  for( size_t i = 1; i < buf.GetSize(); i++ ) {
        Segment s ( buf[i-1], buf[i] );
        if( s.IsPointIn( p ) ) {
            return true;
        }
    }
    Segment s ( buf[0], buf[buf.GetSize()-1] );
    if( s.IsPointIn( p ) ) {
        return true;
    }
   
	Vector v1, v2;
	double alpha = 0;
	v1 = Vector( buf[buf.GetSize()-1].GetX() - p.GetX(), buf[buf.GetSize()-1].GetY() - p.GetY() );
	v2 = Vector( buf[0].GetX() - p.GetX(), buf[0].GetY() - p.GetY() );
	alpha += atan2( VectorProduct( v1, v2 ), ScalarProduct( v1, v2 ) );
	for( size_t i = 1; i < buf.GetSize(); i++ ) {
		v1 = Vector( buf[i-1].GetX() - p.GetX(), buf[i-1].GetY() - p.GetY() );
		v2 = Vector( buf[i].GetX() - p.GetX(), buf[i].GetY() - p.GetY() );
		alpha += atan2( VectorProduct( v1, v2 ), ScalarProduct( v1, v2 ) );
	}
	if( fabs( alpha ) < eps ) {
		return false;
	}
	else {
		return true;
	}
}

Intersection Polygon::Intersect( const Segment& s ) const {
	Intersection result;
	for( size_t i = 0; i < buf.GetSize() - 1; i++ ) {
		Segment current( buf[i], buf[i+1] );
		result.AddIntersection( current.Intersect( s ) );
	}
	Segment current( buf[0], buf[buf.GetSize()-1] );
	result.AddIntersection( current.Intersect( s ) );
	return result;
}

Functor::Functor() : o() {
}

Functor::Functor( const Point& p ) : o( p ) {
}

bool Functor::operator()( const Point& p1, const Point& p2 ) {
	if( o == p1 ) {
		return true;
	}
	else if( o == p2 ) {
		return false;
	}
	Vector v1( o, p1 ), v2( o, p2 ), v( 1, 0 );
	double d1 = ScalarProduct( v, v1 ) / Distance( o, p1 ), d2 = ScalarProduct( v, v2 ) / Distance( o, p2 );
	return d2 < d1;
}

Polygon Polygon::ConvexHull() const {
	if( buf.GetSize() <= 2 ) {
		return *this;
	}
	else {
		CArray<Point> res;
		CArray<Point> s( buf );
		Point pmin( buf[0] );
		for( size_t i = 1; i < buf.GetSize(); i++ ) {
			if( buf[i].GetY() < pmin.GetY() ) {
				pmin = buf[i];
			}
			else if( buf[i].GetY() == pmin.GetY() ) {
				if( buf[i].GetX() < pmin.GetX() ) {
					pmin = buf[i];
				}
			}
		}
		Functor f( pmin );
		QSort( &s[0], &s[s.GetSize()-1], f ); 	
		res.PushBack( s[0] );
		res.PushBack( s[1] );
		bool flag, flagg;
		for( size_t j = 2; j < s.GetSize(); j++ ) {
			//if( s[j].GetX() == -3936 && s[j].GetY() == 797 ) {
				//system("pause");
			//}
			flag = true;
			flagg = true;
			while( flag && flagg && res.GetSize() > 1 ) {
				Vector v1( res[res.GetSize()-2], res[res.GetSize()-1]), v2( res[res.GetSize()-1], s[j] );
				double pr = VectorProduct( v1, v2 );
				if( pr < 0 ) {
					res.PopBack();
				}
				else if( pr == 0 ) {
					if( ScalarProduct( v1, v2 ) > 0 ) {
						res.PopBack();
					}
					else {
						if( Distance( res[res.GetSize()-1], res[res.GetSize()-2] ) < Distance( res[res.GetSize()-1], s[j] ) ) {
							res.PopBack();
						}
						else {
							flagg = false;
						}
					}
				}
				else {
					flag = false;
				}
			}
			if( flagg ) {
				res.PushBack( s[j] );
			}
		}
		Vector v1( res[res.GetSize()-2], res[res.GetSize()-1] ), v2( res[res.GetSize()-1], res[0] );
		if( VectorProduct( v1, v2 ) == 0 ) {
			res.PopBack();
		}
		Polygon result( res );
		return result;
	}
}
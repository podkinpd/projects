#include "Vector.h"

Vector::Vector() : x(0), y(0) {
}

Vector::Vector( double nx, double ny ) : x(nx), y(ny) {
}

Vector::Vector( const Point& first, const Point& second ) : x( second.GetX() - first.GetX() ), y( second.GetY() - first.GetY() ) {
}

Vector::Vector( const Vector& v ) : x(v.x), y(v.y) {
}

Vector& Vector::operator=( const Vector& v ) {
	x = v.x;
	y = v.y;
	return *this;
}

double ScalarProduct( const Vector& v1, const Vector& v2 ) {
	return v1.x * v2.x + v1.y * v2.y;
}

double VectorProduct( const Vector& v1, const Vector& v2 ) {
	return v1.x * v2.y - v1.y * v2.x;
}
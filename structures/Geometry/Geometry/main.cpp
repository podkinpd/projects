#include <iostream>
#include <fstream>
#include "Shape.h"
#include "Point.h"
#include "Segment.h"
#include "Polygon.h"
#include "Vector.h"

double min( double d1, double d2 ) {
	return ( d1 < d2 ) ? d1 : d2;
}

int main() {
	CArray<int> v;
	v[5] = 0;
	std::ifstream in;
	in.open("input.txt");
	int n;
	double a, b;
	CArray<Point> arr;
	in >> n;
	//std::cin >> n;
	for( int i = 0; i < n; i++ ) {
		in >> a >> b;
		//std::cin >> a >> b;
		Point p( a, b );
		arr.PushBack( p );
	}
	Polygon p( arr );
	Polygon pp( p.ConvexHull() );
/*	for( int i = 0; i < pp.GetLinkToBuf().GetSize(); i++ ) {
		std::cout << pp[i].GetX() << ' ' << pp[i].GetY() << std::endl;
	}*/
	double per = 0, pl = 0;
	for( int i = 1; i < pp.GetLinkToBuf().GetSize(); i++ ) {
		per += Distance( pp[i-1], pp[i] );
	}
	per += Distance( pp[0], pp[pp.GetLinkToBuf().GetSize()-1] );
	for( int i = 1; i < pp.GetLinkToBuf().GetSize() - 1; i++ ) {
		Vector v1( pp[0], pp[i] ), v2( pp[0], pp[i+1] );
		pl += ( 0.5 * VectorProduct( v1, v2 ) );
	}
	std::cout << per << std::endl;
	std::cout << pl << std::endl;
	in.close();
	system("pause");
	return 0;
}
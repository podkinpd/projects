#include <iostream>
#include <stdio.h>
#include "SegmentTree.h"
#include <iterator>


class func {
	const static long long neutral = 0;
public:
	long long operator()( long long a, long long b ) const {
		return a + b;
	}
	long long getNeutral() const {
		return neutral;
	}
};


int main() {
	long long n;
	std::cin >> n;
	std::vector<long long> v;
	long long a;
	for( long long i = 0; i < n; i++ ) {
		std::cin >> a;
		v.push_back( a );
	}
	std::vector<long long>::iterator iit = v.begin(), eos = v.end();
	SegmentTree<long long, func > s( iit, eos );
	std::cin >> a;
	char c;
	long long l, r;
	for( long long i = 0; i < a; i++ ) {
		std::cin >> c;
		if( c == 's' ) {
			std::cin >> l >> r;
			std::cout << s.query( l , r ) << std::endl;
		}
		else {
			std::cin >> l >> r;
			s.change( r, l );
		}
	}
	return 0;
}
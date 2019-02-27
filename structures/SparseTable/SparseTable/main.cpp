#include "SparseTable.h"
#include <iterator>
#include <iostream>

class func {
	std::pair<int, int> neutral;
public:
	func() : neutral( std::make_pair( -2147483647, 0 ) ) {}
	std::pair<int, int> operator()( std::pair<int, int> a, std::pair<int, int> b ) const {
		return ( a.first > b.first ) ? a : b;
	}
	std::pair<int, int> getNeutral() const {
		return neutral;
	}
};

int main() {
	std::vector<std::pair<int,int>> v;
	int a, n;
	std::cin >> n;
	for(  int i = 0; i < n; i++ ) {
		std::cin >> a;
		v.push_back( std::make_pair( a, i + 1 ) );
	}
	auto iit = v.begin(), eos = v.end();
	SparseTable< std::pair< int, int >, func > s( iit, eos );
	std::cin >> a;
	int l, r;
	std::pair<int,int> p;
	for( int i = 0; i < a; i++) {
		std::cin >> l >> r;
		p = s.query( l, r );
		std::cout << p.first << ' ' << p.second << std::endl;
	}
	
	system("pause");
	return 0;
}
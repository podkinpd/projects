#include "PriorityQueue.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>


class more {
public:
	template< typename T >
	bool operator()( T t1, T t2 ) {
		return t1 > t2;
	}
};

int main() {

	std::vector<int> v;
	v.push_back(5);
	v.push_back(1);
	v.push_back(7);
	v.push_back(2);
	v.push_back(0);
	v.push_back(9);
	std::vector<int>::iterator it1 = v.begin(), it2 = v.end();
	PrQueue< int > q;
	q.push( 5 );
	q.push( 1 );
	q.push( 2 );
	std::cout << q.top();
	system("pause");
	return 0;
}







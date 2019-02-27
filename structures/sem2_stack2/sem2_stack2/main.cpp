#include <iostream>
#include "stack.h"
#include "algorithm.h"

int main() {
	std::cout << "Enter number of expressions." << std::endl;
	int n;
	std::cin >> n;
	std::cout << "Enter expression with spaces after all signs and numbers. Last symbol must be a point." << std::endl;
	for( int i = 0; i < n; i++ ) {
		std::cout << algorithm() << std::endl;
	}


}
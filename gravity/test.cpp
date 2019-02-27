#include <iostream>
#include <vector>

template <typename T>
int testF(std::vector<T> t) {
    t.clear();
    return 1;
}


int main() {
	int a = 1;
	std::vector<double> t;
	for(int i = 1; i < 10; i++ ) {
                 t.push_back( 0.0001*i);
	}
	std::cout << testF(t) << std::endl;
	return 0;
}

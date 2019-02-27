#include <iostream>
#include "CArray.h"

int main() {
	CArray<int> a;
	for( int i = 0; i < 11; i++ ) {
		a.PushBack( rand() % 100 );
	}
	std::cout<< a.GetBufferSize() << ' ' << a.GetSize() << std::endl;

	a.PushBack( 111 );
	a[5] = 228;
	for( int i = 0; i < 12; i++ ) {
		std::cout << a[i] << ' ';
	}
	return 0;
}
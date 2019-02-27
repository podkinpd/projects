#include "stack.h"
#include "algorithm.h"
#include <iostream>

using namespace StaticStack;

int algorithm() {
	Stack s;
	int a = 0, b = 0;
	char c;
	c = getchar();
	while( c != '.' ) {
		if( c == '+' || c == '-' || c == '*' ) {
			b = s.Pop();
			a = s.Pop();
			if( c == '+' ) {
				s.Push( a + b );
			}
			if( c == '-' ) {
				s.Push( a - b );
			}
			if( c == '*' ) {
				s.Push( a * b );
			}
			c = getchar();
		}
		else if( c == ' ' ) {
			c = getchar();
		}
		else {
			while( c != ' ' ) {
				a = 0;
				a = a* 10 + c - 48;
				c = getchar();
			}
			s.Push( a );
		}
	}

	return s.Pop();	
}

#include "Heap.h"

template< typename T, typename Cmp = defaultmore, typename Container = std::vector<T> >
class PrQueue : private Heap< T, Cmp, Container > {
public : 
	PrQueue() : Heap< T, Cmp, Container>() {}
	PrQueue( const PrQueue& p ) : Heap< T, Cmp, Container>( p ) {}
	PrQueue( PrQueue&& p ) : Heap< T, Cmp, Container>( p ) {}

	void push( const T& t ) {
		return Heap::push( t );
	}
	void push( T&& t ) {
		return Heap::push( t );
	}

	bool empty() const {
		return Heap::empty();
	}

	T top() const {
		return Heap::top();
	}

	T pop() {
		return Heap::pop();
	}
};
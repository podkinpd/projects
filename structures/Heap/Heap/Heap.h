#pragma once
#include <vector>

class defaultmore {
public:
	template< typename T >
	bool operator()( T t1, T t2 ) {
		return t1 > t2;
	}
};

template< typename T, typename Cmp = defaultmore, typename Container = std::vector<T> >
class Heap {
protected:
	Container c;
	Cmp cmp;
private:
	typedef typename Container::iterator ContIterator; 

	void swap( ContIterator it1, ContIterator it2 ) {
		T t = *it1;
		*it1 = *it2;
		*it2 = t;
		return;
	}
	void sift_up( ContIterator it ) {
		ContIterator i, beg = c.begin();
		while( it - beg > 0 ) {
			i = beg + ( it - beg - 1 ) / 2;
			if( !cmp( *it, *i ) ) {
				swap( i, it );
			}
			it = i;
		}
		return;
	}
	void sift_down( ContIterator it, ContIterator last ) {
		ContIterator beg = c.begin();
		size_t l, r;
		while( last - it > 0 ) {
			l = 2 * ( it - beg + 1 ) - 1;
			r = l + 1;
			if( l > last - beg ) return;
			else if( l == last - beg ) {
				if( !cmp( *last, *it ) ) {
					swap( it, last );
				}
				return;
			}
			else {
				if( cmp( *( beg + r ), *( beg + l ) ) ) {
					if( !cmp( *( beg + l ), *it ) ) {
						swap( it, beg + l );
						it = beg + l;
					}
					else return;
				}
				else {
					if( !cmp( *( beg + r ), *it ) ) {
						swap( it, beg + r );
						it = beg + r;
					}
					else return;
				}
			}
		}
		return;
	}
	void make_heap() {
		ContIterator beg = c.begin(), last = c.end() - 1, it = beg + ( last - beg + 1 ) / 2 - 1;
		for( ; it - beg > 0; it-- ) {
			sift_down( it, last );
		}
		sift_down( it, last );
		return;
	}
public:
	typedef Heap< T, Cmp, Container > MyT;

	Heap() : c(), cmp()  {}
	Heap( const MyT& h ) : c( h.c ), cmp( h.cmp ) {}
	Heap( MyT&& h ) : c( std::move( h.c ) ), cmp( std::move( h.cmp ) ) {}
	Heap( const Container& cont ) : c( cont ), cmp() { make_heap(); }
	Heap( Container&& cont ) : c( std::move( cont ) ), cmp() { make_heap(); }
	
	template< typename InIt >
	Heap( InIt it1, InIt it2 ) : c( it1, it2 ), cmp() { make_heap(); }
	
	MyT& operator=( const MyT& h ) {
		c = h.c;
		return( *this );
	}
	MyT& operator=( MyT&& h ) {
		c = std::move( h.c );
		return( *this );
	}

	void push( const T& t ) {
		c.push_back( t );
		sift_up( c.end() - 1 );
		return;
	}
	void push( T&& t ) {
		c.push_back( t );
		sift_up( c.end() - 1 );
		return;
	}

	bool empty() const {
		return c.empty();
	}
	T top() const {
		if( !empty() )
		return *( c.begin() );
	}
	T pop() {
		if( !empty() ) {
			if( c.size() == 1 ) {
				T t = *( c.begin() );
				c.pop_back();
				return t;
			}
			ContIterator it = c.end() - 1;
			T t = *( c.begin() );
			swap( it, c.begin() );
			it--;
			c.pop_back();
			sift_down( c.begin(), it );
			return t;
		}
	}
};

template< typename RndIt, typename Comp >
void sortHeap( RndIt left, RndIt right, Comp comp = 0 ) {
	if( left == right ) return;
	Heap< RndIt::value_type, Comp > h( left, right );
	RndIt it = left;
	for( ; it < right; it++ ) {
		*it = h.pop();
	}
	return;
}
#include <vector>

template< typename T, typename Func >
class SegmentTree {
protected:
	std::vector< T > buffer;
	Func func;
public:
	SegmentTree( const SegmentTree& t ) : buffer( t.buffer ), func( t.func ) {}
	SegmentTree( SegmentTree&& t ) : buffer( std::move( t.buffer ) ), func( t.func ) {}

	template< typename InIt >
	SegmentTree( InIt it1, InIt it2 ) : buffer(), func() {
		std::vector<T> v( it1, it2 );
		size_t n = v.size();
		size_t nmax = 1;
		while( nmax < n ) nmax = nmax << 1;
		buffer.resize( ( nmax << 1 ) - 1 );
		for( size_t i = nmax - 1 + n; i < buffer.size(); i++ ) buffer[i] = func.getNeutral();
		for( size_t i = nmax - 1; i < nmax - 1 + n; i++ ) buffer[i] = v[i - nmax + 1 ];
		for( size_t i = nmax - 1; i > 0; i-- ) buffer[i - 1] = func( buffer[2 * i - 1], buffer[2 * i] );
	}

	T query( size_t left, size_t right ) const {
		T fl, fr;
		left--;
		right--;
		fl = fr = func.getNeutral();
		size_t l = left + ( buffer.size() >> 1 ), r = right + ( buffer.size() >> 1 );
		while( l < r ) {
			if( l % 2 == 0 ) {
				fl = func( buffer[l], fl );
				l++;
			}
			if( r % 2 == 1 ) {
					fr = func( buffer[r], fr );
					r--;
			}
			l = ( l - 1 ) >> 1;
			r = ( r - 1 ) >> 1;
			
		}
		if( l == r ) return func( fl, func( buffer[r], fr ) );
		else return func( fl, fr );
	}
	
	void change( T t, size_t i ) {
		size_t n = buffer.size() >> 1;
		i--;
		n += i;
		buffer[ n ] = t;
		T c, nc;
		size_t nn, nl;

		while( n > 0 ) {
			if( n % 2 == 0 ) {
				nl = n - 1;
			}
			else {
				nl = n + 1;
			}
			nn = ( n - 1 ) >> 1;
			nc = func( buffer[nl], buffer[n] );
			if( buffer[nn] == nc ) break;
			else {
				buffer[nn] = nc;
				n = nn;
			}
		}
		return;
	}

};
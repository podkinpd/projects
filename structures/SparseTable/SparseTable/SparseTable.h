#include <vector>

template< typename T, typename Func >
class SparseTable {
protected:
	std::vector< std::vector<T> > buffer;
	std::vector<size_t> log2n;
	Func func;
public:
	template< typename InIt >
	SparseTable( InIt it1, InIt it2 ) {
		std::vector<T> v( it1, it2 );
		size_t l, n, k = 0;
		l = n = v.size();
		while( l > 0 ) {
			l = l >> 1;
			k++;
		}
		buffer.resize( k );
		buffer[0] = v;
		l = 1;
		for( size_t i = 1; i < k; i++ ) {
			buffer[i].resize( n - ( l << 1 ) + 1 );
			for( size_t j = 0; j < n - ( l << 1 ) + 1; j++ ) {
				buffer[i][j] = func( buffer[i - 1][j], buffer[i - 1][j + l] );
			}
			l = l << 1;
		}

		log2n.resize( n + 1 );
		log2n[1] = 0;
		log2n[2] = 1;
		l = 4;
		k = 3;
		while( k <= n ) {
			while( k < l && k <= n ) {
				log2n[k] = log2n[l >> 1 ];
				k++;
			}
			if( k <= n ) {
				log2n[k] = log2n[k >> 1 ] + 1;
				k++;
			}
			l = l << 1;	
		}
	}

	T query( size_t left, size_t right ) const {
		left--;
		right--;
		size_t k = log2n[ right - left + 1];
		return func( buffer[k][left], buffer[k][right - ( 1 << k ) + 1] );
	}
};

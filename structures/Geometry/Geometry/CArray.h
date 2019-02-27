#pragma once
#include <exception>
#include <iostream>

class indexException : public std::exception {
private:
	int i;
public:
	virtual const char* what() const throw() {
		return " Bad_index : ";
	}
	void push( int j ) {
		i = j;
	}
	int getI() {
		return i;
	}
};

template <typename type_t>
class CArray {
private:
	size_t bufferSize;
	size_t size;
	type_t* buffer;

	static const size_t startBufferSize = 10;
	static const size_t increasingFactor = 2;
public:
	CArray();
	CArray( size_t );
	CArray( const CArray& );
	~CArray();

	size_t GetSize() const;
	size_t GetBufferSize() const;
//	size_t GetIncreasingFactor() const;
	void IncreaseBuffer();

	void SetSize( size_t );
	void SetBufferSize( size_t );
//	void SetIncreasingFactor( size_t );	
		
	bool IsEmpty() const;
	
	const type_t& operator[]( size_t ) const;
	type_t& operator[]( size_t );
	CArray<type_t>& operator=( const CArray& );
	
	void PushBack( type_t );
	void PopBack();

	template<typename type_t, class predicat> friend void QSort( type_t*, type_t*, predicat );
};

template <typename type_t> CArray<type_t>::CArray() {
	try {
		buffer = new type_t[startBufferSize];
	}
	catch( std::bad_alloc& ba ) {
		std::cerr << "Bad_alloc : " << ba.what() << '\n';
	}
	size = 0;
	bufferSize = startBufferSize;
}

template <typename type_t> CArray<type_t>::CArray( size_t bufSize ) {
	try {
		buffer = new type_t[bufSize];
	}
	catch( std::bad_alloc& ba ) {
		std::cerr << "Bad_alloc : " << ba.what() << '\n';
	}
	size = 0;
	bufferSize = bufSize;
}

template <typename type_t> CArray<type_t>::CArray( const CArray& arr ) {
	bufferSize = arr.bufferSize;
	size = arr.size;
	try {
		buffer = new type_t[bufferSize];
	}
	catch( std::bad_alloc& ba ) {
		std::cerr << "Bad_alloc : " << ba.what() << '\n';
	}
	for( size_t i = 0; i < size; i++ ) {
		buffer[i] = arr[i];
	}
}

template <typename type_t> CArray<type_t>::~CArray() {
	delete [] buffer;
	buffer = nullptr;
}

template <typename type_t> size_t CArray<type_t>::GetSize() const {
	return size;
}

template <typename type_t> size_t CArray<type_t>::GetBufferSize() const {
	return bufferSize;
}

/*template <typename type_t> size_t CArray<type_t>::GetIncreasingFactor() {
	return increasingFactor;
}*/

template <typename type_t> void CArray<type_t>::SetSize( size_t index ) {
	if( bufferSize < index ) {
		SetBufferSize( size_t( increasingFactor * index ) );
		size = index;
	}
	else {
		size = index;
	}
}

template <typename type_t> void CArray<type_t>::SetBufferSize( size_t index ) {
	try {
		type_t* arr = new type_t[index];
		for( size_t i = 0; i < size; i++ ) {
			arr[i] = buffer[i];
		}
		delete [] buffer;
		buffer = arr;
		bufferSize = index;
	}
	catch( std::bad_alloc& ba ) {
		std::cerr << "Bad_alloc : " << ba.what() << '\n';
	}
}

/*template <typename type_t> void CArray<type_t>::SetIncreasingFactor( size_t index ) {
	increasingFactor = index;
}*/

template <typename type_t> void CArray<type_t>::IncreaseBuffer() {
	SetBufferSize( size_t(bufferSize * increasingFactor) );
}

template <typename type_t> const type_t& CArray<type_t>::operator[]( size_t index ) const {
	try {
		if( index < 0 || index > size ) {
			indexException inEx;
			inEx.push( index );
			throw inEx;
		}
	}
	catch( indexException& ie ) {
		std::cerr << ie.what() << ie.getI() << '\n';
	}
	return buffer[index];
}

template <typename type_t> type_t& CArray<type_t>::operator[]( size_t index ) {
	try {
		if( index < 0 || index > size ) {
			indexException inEx;
			inEx.push( index );
			throw inEx;
		}
	}
	catch( indexException& ie ) {
		std::cerr << ie.what() << ie.getI() << '\n';
	}
	return buffer[index];
}

template <typename type_t> CArray<type_t>& CArray<type_t>::operator=( const CArray<type_t>& arr ) {
	bufferSize = arr.bufferSize;
	size = arr.size;
	delete [] buffer;
	buffer = new type_t[bufferSize];
	for( size_t i = 0; i < size; i++ ) {
		buffer[i] = arr[i];
	}
	return *this;
}

template <typename type_t> void CArray<type_t>::PushBack( type_t t ) {
	if( bufferSize == size ) {
		IncreaseBuffer();
	}
	buffer[size] = t;
	size++;
}

template <typename type_t> void CArray<type_t>::PopBack() {
	size--;
}

template <typename type_t, class predicat> void QSort( type_t* left, type_t* right, predicat func ) {
	if( left >= right ) {
		return;
	}
	if( left == right - 1 ) {
		if( !func( *left, *right ) ) {
			type_t c = *left;
			*left = *right;
			*right = c;
		}
		return;
	}
	type_t* m = right;
	type_t* l = left;
	type_t* r = right - 1;
	while( l < r ) {
		while( func( *l, *m ) && l < r ) {
			l++;
		}
		while( !func( *r, *m ) && l < r ) {
			r--;
		}
		if( l != r ) {
			type_t c = *l;
			*l = *r;
			*r = c;
		}
	}
	if( !func( *l , *m ) ) {
		type_t c = *l;
		*l = *right;
		*right = c;
	}
	QSort( left, l, func );
	QSort( r + 1, right, func );
	return;
}
#include "stack.h"
#include <iostream>

namespace DinamicStack {

	Stack::Stack() {
		this->size = 0;
		this->top = 0;
	}

	int Stack::Size() {
		return this->size;
	}

	void Stack::Push( myType c ) {
		Node* NewNode = new Node;
		NewNode->c = c;
		NewNode->prev = this->top;
		this->top = NewNode;
		this->size++;
	}

	myType Stack::Top() {
		if( this->size == 0 ) {
			std::cerr << "no elements in stack" << std::endl;
		}
		else {
			return this->top->c;
		}
	}

	myType Stack::Pop() {
		if( this->size == 0 ) {
			std::cerr << "no elements in stack" << std::endl;
		}
		else {
			myType c = this->top->c;
			Node* ptr = this->top;
			this->top = this->top->prev;
			delete ptr;
			this->size--;
			return c;
		}
	}

	void Stack::Clear() {
		Node* ptr;
		for( int i = 0; i < this->size; i++ ) {
			ptr = this->top;
			this->top = this->top->prev;
			delete ptr;
		}
		this->size = 0;
	}

}

namespace StaticStack {

	Stack::Stack() {
		currentNumber = 0;
	}

	void Stack::Push( myType c ) {
		arr[currentNumber] = c;
		currentNumber++;
		return;
	}

	myType Stack::Pop() {
		currentNumber--;
		return arr[currentNumber];
	}

	myType Stack::Top() {
		return arr[currentNumber - 1];
	}

	bool Stack::IsEmpty() {
		if( currentNumber == 0 ) {
			return true;
		}
		else {
			return false;
		}
	}

	void Stack::Clear() {
		currentNumber = 0;
		return;
	}

	int Stack::Size() {
		return currentNumber;
	}

}
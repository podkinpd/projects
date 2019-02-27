#ifndef __STACK_H_
#define __STACK_H_

typedef int myType;

namespace DinamicStack {

	class Stack {
	private:
		struct Node {
			Node* prev;
			myType c;
		};
		Node* top;
		int size;
	public:
		Stack();
		int Size();
		void Push( myType c );
		myType Pop();
		myType Top();
		void Clear();
	};

}

namespace StaticStack {

	class Stack {
	private:
		myType arr[200];
		int currentNumber;
	public:
		Stack();
		void Push( myType c );
		myType Pop();
		myType Top();
		bool IsEmpty();
		void Clear();
		int Size();
	};

}

#endif
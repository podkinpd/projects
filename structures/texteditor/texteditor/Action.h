#pragma once
#include "Cursor.h"

class Text;

class Action {
public:
	virtual void operator()( Cursor&, Text& ); 
	virtual void UndoIt( Cursor&, Text& );
};

class Undo : public Action {
public:
	void operator()( Cursor&, Text& );
	void UndoIt( Cursor&, Text& );
};

class Redo : public Action {
public:
	void operator()( Cursor&, Text& );
	void UndoIt( Cursor&, Text& );
};

class MoveCursorLeft : public Action {
public:
	void operator()( Cursor&, Text& );
	void UndoIt( Cursor&, Text& );
};

class MoveCursorRight : public Action {
public:
	void operator()( Cursor&, Text& );
	void UndoIt( Cursor&, Text& );
};

class MoveCursorUp : public Action {
public:
	void operator()( Cursor&, Text& );
	void UndoIt( Cursor&, Text& );
};

class MoveCursorDown : public Action {
public:
	void operator()( Cursor&, Text& );
	void UndoIt( Cursor&, Text& );
};

class InsertSymbol : public Action {
private:
	char symbol;
public:
	InsertSymbol( char );
	void operator()( Cursor&, Text& );
	void UndoIt( Cursor&, Text& );
	char GetSymbol();
};

class DeleteSymbol : public Action {
private:
	char symbol;
public:
	void operator()( Cursor&, Text& );
	void UndoIt( Cursor&, Text& );
	char GetSymbol();
};
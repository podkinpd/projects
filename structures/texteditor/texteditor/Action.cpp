#include "Action.h"

class Text;

void MoveCursorLeft::operator()( Cursor& c, Text& t ) {
	if( t.GetNumberOfUndoActions() > 0 ) {
		t.ClearUndoStack();
	}
	if( c.number > 0 ) {
		c.number--;
		t.AddAction( this );
	}
}

void MoveCursorLeft::UndoIt( Cursor& c, Text& t ) {
	MoveCursorRight* a = new MoveCursorRight;
	(*a)( c, t );
	t.DeleteAction();
	t.AddUndoAction( this );
}

void MoveCursorRight::operator()( Cursor& c, Text& t ) {
	if( t.GetNumberOfUndoActions() > 0 ) {
		t.ClearUndoStack();
	}
	if( c.number < t.GetSizeOfRow( c.row ) ) {
		c.number++;
		t.AddAction( this );
	}
}

void MoveCursorRight::UndoIt( Cursor& c, Text& t ) {
	MoveCursorLeft* a = new MoveCursorLeft;
	(*a)( c, t );
	t.DeleteAction();
	t.AddAction( this );
}

void MoveCursorUp::operator()( Cursor& c, Text& t ) {
	if( t.GetNumberOfUndoActions() > 0 ) {
		t.ClearUndoStack();
	}
	if( c.row > 0 ) {
		c.row--;
		t.AddAction( this );
	}
}

void MoveCursorUp::UndoIt( Cursor& c, Text& t ) {
	MoveCursorDown* a = new MoveCursorDown;
	(*a)( c, t );
	t.DeleteAction();
	t.AddUndoAction( this );
}

void MoveCursorDown::operator()( Cursor& c, Text& t ) {
	if( t.GetNumberOfUndoActions() > 0 ) {
		t.ClearUndoStack();
	}
	if( c.row + 1 < t.GetNumberOfRows() ) {
		c.row++;
		t.AddAction( this );
	}
}

void MoveCursorDown::UndoIt( Cursor& c, Text& t ) {
	MoveCursorUp* a = new MoveCursorUp;
	(*a)( c, t );
	t.DeleteAction();
	t.AddUndoAction( this );
}

InsertSymbol::InsertSymbol( char ch ) : symbol(ch) {}

void InsertSymbol::operator()( Cursor& c, Text& t ) {
	t[c.row].insert( c.number, 1, symbol );
	MoveCursorRight* a = new MoveCursorRight;
	(*a)( c, t );
	t.AddAction( this );
}

void InsertSymbol::UndoIt( Cursor& c, Text& t ) {
	if( t.GetNumberOfUndoActions() > 0 ) {
		t.ClearUndoStack();
	}
	MoveCursorLeft* a = new MoveCursorLeft;
	(*a)( c, t );
	DeleteSymbol* d = new DeleteSymbol;
	(*d)( c, t );
	t.DeleteAction();
	t.AddUndoAction( this );
}

char InsertSymbol::GetSymbol() {
	return symbol;
}

void DeleteSymbol::operator()( Cursor& c, Text& t ) {
	if( t.GetNumberOfUndoActions() > 0 ) {
		t.ClearUndoStack();
	}
	if( c.number != t.GetSizeOfRow( c.row ) ) {
		symbol = t[c.row][c.number];
		t[c.row].erase( c.number, 1 );
		t.AddAction( this );
	}
}

void DeleteSymbol::UndoIt( Cursor& c, Text& t ) {
	InsertSymbol* a = new InsertSymbol( symbol );
	(*a)( c, t );
	t.DeleteAction();
	t.AddUndoAction( this );
}

void Undo::operator()( Cursor& c, Text& t ) {
	if( t.GetNumberOfUndoActions() > 0 ) {
		t.ClearUndoStack();
	}
	if( t.GetNumberOfActions() > 0 ) {
		Action* a = t.GetLastAction();
		a->UndoIt( c, t );
	}
}

void Undo::UndoIt( Cursor& c, Text& t ) {
	return;
}

void Redo::operator()( Cursor& c, Text& t ) {
	if( t.GetNumberOfUndoActions() > 0 ) {
		Action* a = t.GetLastUndoAction();
		(*a)( c, t );
		t.DeleteUndoAction();
	}
}

void Redo::UndoIt( Cursor& c, Text& t ) {
	return;
}
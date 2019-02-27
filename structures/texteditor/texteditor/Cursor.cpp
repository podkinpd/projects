#include "Cursor.h"
#include "Text.h"

Cursor::Cursor( Text& t ) : row(0), number(0), text(t) {}

Cursor::Cursor( const Cursor& c ) : row(c.row), number(c.number), text(c.text) {}

void Cursor::MoveLeft() {
	if( number > 0 ) {
		number--;
	}
}

void Cursor::MoveRight() {
	if( number < text.GetSizeOfRow( row ) ) {
		number++;
	}
}

void Cursor::MoveUp() {
	if( row > 0 ) {
		row--;
	}
}

void Cursor::MoveDown() {
	if( row < text.GetNumberOfRows() ) {
		row++;
	}
}
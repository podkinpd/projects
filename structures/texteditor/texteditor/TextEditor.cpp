#include "TextEditor.h"

TextEditor::TextEditor() : text(), curs() {}

void TextEditor::SymbolIn( char ch ) {
	switch( ch ) {
		case '<' : 
			{
				MoveCursorLeft a;
				a( curs, text );
			}
			break;
		case '>' :
			{
				MoveCursorRight a;
				a( curs, text );
			}
			break;
		case '|' : 
			{
			MoveCursorDown a;
			a( curs, text );
			}
			break;
		case '^' :
			{
			MoveCursorUp a;
			a( curs, text );
			}
			break;
		case '#' :
			{
			DeleteSymbol a;
			a( curs, text );
			}
			break;
		case '@' :
			{
			Undo a;
			a( curs, text );
			}
			break;
		case '$' :
			{
			Redo a;
			a( curs, text );
			}
			break;
		default: 
			{
			InsertSymbol a( ch );
			a( curs, text );
			}
	}
}

void TextEditor::PrintText( std::ostream& out ) {
	out << text;
}
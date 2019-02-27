#pragma once
//#include "Action.h"
#include "Text.h"
class Text;

class TextEditor {
private:
	Text text;
	Cursor curs;

public:
	TextEditor();
	void SymbolIn( char ch );
	void PrintText( std::ostream& );

;};
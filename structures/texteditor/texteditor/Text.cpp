#include "Text.h"

Text::Text() : text() {}

Text::Text( const Text& t ) : text(t.text) {}

std::string& Text::operator[]( size_t i ) {
	return text[i];
}

const std::string Text::operator[]( size_t i ) const {
	return text[i];
}

size_t Text::GetNumberOfRows() const {
	return text.size();
}

size_t Text::GetSizeOfRow( size_t i ) const {
	return text[i].size();
}

void Text::AddAction( Action* a ) {
	lastActions.push( a );
}

void Text::AddUndoAction( Action* a ) {
	lastUndoActions.push( a );
}

Action* Text::GetLastAction() {
	return lastActions.top();
}

Action* Text::GetLastUndoAction() {
	return lastUndoActions.top();
}

size_t Text::GetNumberOfActions() {
	return lastActions.size();
}

size_t Text::GetNumberOfUndoActions() {
	return lastUndoActions.size();
}

void Text::DeleteAction() {
	lastActions.pop();
}

void Text::DeleteUndoAction() {
	lastUndoActions.pop();
}

void Text::ClearUndoStack() {
	while( lastUndoActions.size() > 0 ) {
		lastUndoActions.pop();
	}
}

std::ostream& operator<<( std::ostream& out, const Text& t ) {
	std::string s;
	for( size_t i = 0; i < t.GetNumberOfRows(); i++ ) {
		s =  t[i];
		for( size_t j = 0; j < s.size(); j++ ) {
			out << s[j];
		}
		out << '\n';
	}
}
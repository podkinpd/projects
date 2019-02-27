#pragma once
#include "Action.h"
#include <string>
#include <vector>
#include <stack>
#include <iostream>

class Text {
private:
	std::vector<std::string> text;
	std::stack<Action*> lastActions;
	std::stack<Action*> lastUndoActions;
public:
	Text();
	Text( const Text& );
	
	std::string& operator[]( size_t );
	const std::string operator[]( size_t ) const;
	size_t GetNumberOfRows() const;
	size_t GetSizeOfRow( size_t ) const;

	void AddAction( Action* );
	void AddUndoAction( Action* );
	Action* GetLastAction();
	Action* GetLastUndoAction();
	size_t GetNumberOfActions();
	size_t GetNumberOfUndoActions();
	void DeleteAction();
	void DeleteUndoAction();
	void ClearUndoStack();

	friend std::ostream& operator<<( std::ostream&, const Text& );
};
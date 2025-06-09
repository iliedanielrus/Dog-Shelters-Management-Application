#pragma once
#include <stack>
#include "ICommand.h"
#include <string>
class UndoRedoController
{
private:
	std::stack<ICommand*> undo_stack;
	std::stack<ICommand*> redo_stack;

	void clearUndoStack();
	void clearRedoStack();
public:
	UndoRedoController();
	~UndoRedoController();
	void addCommand(ICommand* new_command);
	void undoCommand();
	void redoCommand();
};

class UndoRedoException : public std::exception
{
private:
	std::string message;

public:
	/// <summary>
	/// Creates an object of type UndoRedoException
	/// </summary>
	/// <param name="message">The message of the exception, represented by a string</param>
	UndoRedoException(std::string message);
	const char* what() const noexcept override;
};

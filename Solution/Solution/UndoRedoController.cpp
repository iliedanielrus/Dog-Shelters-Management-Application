#include "UndoRedoController.h"

void UndoRedoController::clearUndoStack()
{
	while (!this->undo_stack.empty())
	{
		ICommand* current_command = this->undo_stack.top();
		this->undo_stack.pop();
		delete current_command;
	}
}
void UndoRedoController::clearRedoStack()
{
	while (!this->redo_stack.empty())
	{
		ICommand* current_command = this->redo_stack.top();
		this->redo_stack.pop();
		delete current_command;
	}
}

UndoRedoController::UndoRedoController(){}

UndoRedoController::~UndoRedoController()
{
	this->clearRedoStack();
	this->clearUndoStack();
}

void UndoRedoController::addCommand(ICommand* new_command)
{
	this->clearRedoStack();
	this->undo_stack.push(new_command);
}

void UndoRedoController::undoCommand()
{
	if (this->undo_stack.empty())
		throw UndoRedoException("No more undoes!");
	ICommand* command = this->undo_stack.top();
	command->undo();
	this->undo_stack.pop();
	this->redo_stack.push(command);
}

void UndoRedoController::redoCommand()
{
	if (this->redo_stack.empty())
		throw UndoRedoException("No more redoes!");
	ICommand* command = this->redo_stack.top();
	command->redo();
	this->redo_stack.pop();
	this->undo_stack.push(command);
}

UndoRedoException::UndoRedoException(std::string message)
{
	this->message = message;
}

const char* UndoRedoException::what() const noexcept
{
	return this->message.c_str();
}

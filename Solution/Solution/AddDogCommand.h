#pragma once
#include "ICommand.h"
#include "Repository/Repository.h"
class AddDogCommand: public ICommand
{
private:
	Repository& repo;
	Dog added_dog;
public:
	AddDogCommand(Repository& repo, Dog added_dog);
	// Inherited via ICommand
	virtual void execute() override;
	virtual void undo() override;
	virtual void redo() override;
};


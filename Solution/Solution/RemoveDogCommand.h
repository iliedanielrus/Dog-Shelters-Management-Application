#pragma once
#include "ICommand.h"
#include "Repository/Repository.h"
class RemoveDogCommand : public ICommand
{
private:
	Repository& repo;
	Dog removed_dog;

public:
	RemoveDogCommand(Repository& repo, Dog removed_dog);
	// Inherited via ICommand
	virtual void execute() override;
	virtual void undo() override;
	virtual void redo() override;
};


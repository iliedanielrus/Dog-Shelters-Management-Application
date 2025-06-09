#pragma once
#include "ICommand.h"
#include "Repository/Repository.h"
class UpdateDogCommand : public ICommand
{
private:
	Repository& repo;
	Dog old_dog, new_dog;

public:
	UpdateDogCommand(Repository& repo, Dog old_dog, Dog new_dog);
	// Inherited via ICommand
	virtual void execute() override;
	virtual void undo() override;
	virtual void redo() override;
};


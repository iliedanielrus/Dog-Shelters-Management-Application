#pragma once
#include "ICommand.h"
#include "Repository/Repository.h"
class AdoptDogController : public ICommand
{
private:
	Repository& all_dogs_repo, &adoption_repo, &filter_repo;
	Dog dog;
public:
	AdoptDogController(Repository& all_dogs_repo, Repository& adoption_repo, Repository& filter_repo, Dog dog);
	// Inherited via ICommand
	virtual void execute() override;
	virtual void undo() override;
	virtual void redo() override;
};


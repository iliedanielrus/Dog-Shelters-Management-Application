#include "UpdateDogCommand.h"

UpdateDogCommand::UpdateDogCommand(Repository& repo, Dog old_dog, Dog new_dog) : repo{repo}
{
	this->old_dog = old_dog;
	this->new_dog = new_dog;
}

void UpdateDogCommand::execute()
{
	this->old_dog = this->repo.updateElement(old_dog, new_dog);
}

void UpdateDogCommand::undo()
{
	this->repo.updateElement(new_dog, old_dog);
}

void UpdateDogCommand::redo()
{
	this->repo.updateElement(old_dog, new_dog);
}

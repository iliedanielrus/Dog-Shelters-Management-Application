#include "AddDogCommand.h"

AddDogCommand::AddDogCommand(Repository& repo, Dog added_dog):repo{repo}
{
	this->added_dog = added_dog;
}

void AddDogCommand::execute()
{
	this->repo.addElement(added_dog);
}

void AddDogCommand::undo()
{
	this->repo.removeElement(added_dog);
}

void AddDogCommand::redo()
{
	this->repo.addElement(added_dog);
}

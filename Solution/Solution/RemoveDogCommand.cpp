#include "RemoveDogCommand.h"

RemoveDogCommand::RemoveDogCommand(Repository& repo, Dog removed_dog): repo{repo}
{
	this->removed_dog = removed_dog;
}

void RemoveDogCommand::execute()
{
	this->removed_dog = this->repo.removeElement(this->removed_dog);
}

void RemoveDogCommand::undo()
{
	this->repo.addElement(this->removed_dog);
}

void RemoveDogCommand::redo()
{
	this->repo.removeElement(this->removed_dog);
}

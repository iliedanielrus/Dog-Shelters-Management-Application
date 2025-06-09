#include "AdoptDogController.h"

AdoptDogController::AdoptDogController(Repository& all_dogs_repo, Repository& adoption_repo, Repository& filter_repo, Dog dog) : 
	all_dogs_repo{ all_dogs_repo }, adoption_repo{ adoption_repo }, filter_repo{filter_repo}
{
	this->dog = dog;
}

void AdoptDogController::execute()
{
	this->all_dogs_repo.removeElement(this->dog);
	this->adoption_repo.addElement(this->dog);
	this->filter_repo.removeElement(this->dog);
}

void AdoptDogController::undo()
{
	this->all_dogs_repo.addElement(this->dog);
	this->adoption_repo.removeElement(this->dog);
	this->filter_repo.addElement(this->dog);
}

void AdoptDogController::redo()
{
	this->all_dogs_repo.removeElement(this->dog);
	this->adoption_repo.addElement(this->dog);
	try 
	{
		this->filter_repo.removeElement(this->dog);
	}
	catch (RepoException& re)
	{
		return;
	}
}

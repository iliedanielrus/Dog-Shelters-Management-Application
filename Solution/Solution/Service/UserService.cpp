#include <algorithm>
#include "UserService.h"
#include "../AdoptDogController.h"

UserService::UserService(Repository& all_dogs_repo, TextFileRepository& adoption_list_repo, FilterIterationRepo& current_dogs_repo, UndoRedoController& undo_redo_controller) :
	all_dogs_repo{ all_dogs_repo }, adoption_list_repo{ adoption_list_repo }, current_dogs_repo{ current_dogs_repo }, undo_redo_controller{ undo_redo_controller } {}

void UserService::adoptDog(Dog& adopted_dog)
{
	ICommand* command = new AdoptDogController(this->all_dogs_repo, this->adoption_list_repo, this->current_dogs_repo, adopted_dog);
	command->execute();
	this->undo_redo_controller.addCommand(command);
}

const std::vector<Dog>& UserService::getAllDogs() const
{
	return this->all_dogs_repo.getElements();
}

const std::vector<Dog>& UserService::getAdoptedDogs() const
{
	return this->adoption_list_repo.getElements();
}

Dog& UserService::getCurrentDog()
{
	return this->current_dogs_repo.getElement();
}

void UserService::moveToNextDog()
{
	this->current_dogs_repo.nextElement();
}

void UserService::undo()
{
	this->undo_redo_controller.undoCommand();
}

void UserService::redo()
{
	this->undo_redo_controller.redoCommand();
}

void UserService::filterList(int age, std::string breed)
{
	this->current_dogs_repo.setFilterAge(age);
	this->current_dogs_repo.setFilterBreed(breed);
	this->current_dogs_repo.filterRepo(this->all_dogs_repo);
}

const std::string& UserService::getAdoptionListFile() const
{
	return this->adoption_list_repo.getFile();
}

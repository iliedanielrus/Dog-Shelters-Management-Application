#include "AdminService.h"
#include "../Domain/DogValidator.h"
#include <algorithm>
#include "../AddDogCommand.h"
#include "../RemoveDogCommand.h"
#include "../UpdateDogCommand.h"

AdminService::AdminService(Repository& repo, UndoRedoController& undo_redo_controller) : repo{ repo }, undo_redo_controller{undo_redo_controller}{}

void AdminService::addElement(const Dog& new_dog)
{
	DogValidator::validate(new_dog);
	ICommand* command = new AddDogCommand(this->repo, new_dog);
	command->execute();
	this->undo_redo_controller.addCommand(command);
}

void AdminService::removeElement(const std::string& breed, const std::string& name)
{
	Dog delete_form = Dog(breed, name);
	ICommand* command = new RemoveDogCommand(this->repo, delete_form);
	command->execute();
	this->undo_redo_controller.addCommand(command);
}

void AdminService::updateElement(const std::string& old_breed, const std::string& old_name, const Dog& new_dog)
{
	Dog update_form = Dog(old_breed, old_name);
	ICommand* command = new UpdateDogCommand(this->repo, update_form, new_dog);
	command->execute();
	this->undo_redo_controller.addCommand(command);
}

void AdminService::undo()
{
	this->undo_redo_controller.undoCommand();
}

void AdminService::redo()
{
	this->undo_redo_controller.redoCommand();
}

void AdminService::add10Dogs()
{
	this->addElement(Dog("Teckel", "Georgie", 8, "https://www.dogtime.com/assets/uploads/2011/01/file_23020_dachshund-dog-breed.jpg"));
	this->addElement(Dog("Husky", "Blue", 7, "https://s3.publi24.ro/vertical-ro-f646bd5a/extralarge/20200517/0949/0667981e4a814e7d4f38ba450f1750d5.jpg"));
	this->addElement(Dog("Bulldog", "Bernard", 5, "https://s3.amazonaws.com/cdn-origin-etr.akc.org/wp-content/uploads/2017/11/11234019/Bulldog-standing-in-the-grass.jpg"));
	this->addElement(Dog("Labrador", "Goldie", 2, "https://upload.wikimedia.org/wikipedia/commons/thumb/3/34/Labrador_on_Quantock_%282175262184%29.jpg/1200px-Labrador_on_Quantock_%282175262184%29.jpg"));
	this->addElement(Dog("Poodle", "Monsieur", 5, "https://s3.amazonaws.com/cdn-origin-etr.akc.org/wp-content/uploads/2017/11/12225538/Poodle-On-White-03.jpg"));
	this->addElement(Dog("Husky", "Blau", 7, "https://pisicutesicaini.ro/wp-content/uploads/2019/07/Siberian-Husky-standing-outdoors-in-the-winter1.jpg"));
	this->addElement(Dog("Shiba Inu", "Doge", 9, "https://i.kym-cdn.com/entries/icons/original/000/013/564/doge.jpg"));
	this->addElement(Dog("Chihuahua", "Rex", 6, "https://www.thesprucepets.com/thmb/Kh-xt27-hqeQzhyr9288cl_P64I=/1396x1396/smart/filters:no_upscale()/twenty20_f84c633e-705e-4bf8-a724-00cdea750d8d-590b51893df78c92837b18d6.jpg"));
	this->addElement(Dog("Rottweiler", "Fluffy", 3, "https://upload.wikimedia.org/wikipedia/commons/5/57/Rottweiler.jpg"));
	this->addElement(Dog("Corgi", "Mandrew", 5, "https://upload.wikimedia.org/wikipedia/commons/thumb/1/12/ThreeTimeAKCGoldWinnerPembrookeWelshCorgi.jpg/1200px-ThreeTimeAKCGoldWinnerPembrookeWelshCorgi.jpg"));
}


const std::vector<Dog>& AdminService::getAllDogs() const
{
	return this->repo.getElements();
}

std::set<std::string> AdminService::getDogBreeds() const
{
	std::set<std::string> breed_set;
	for (const Dog& dog : this->repo.getElements())
		breed_set.insert(dog.getBreed());
	return breed_set;
}

int AdminService::getNumberOfDogsWithBreed(std::string breed) const
{
	return std::count_if(this->repo.getElements().begin(), this->repo.getElements().end(), [&](Dog dog) {return dog.getBreed() == breed; });
}
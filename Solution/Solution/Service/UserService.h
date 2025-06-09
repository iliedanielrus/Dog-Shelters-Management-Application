#pragma once
#include <vector>
#include "../Repository/Repository.h"
#include "../Repository/TextFileRepo.h"
#include "../FilterIterationRepo.h"
#include "../UndoRedoController.h"

class UserService
{
private:
	Repository& all_dogs_repo;
	TextFileRepository& adoption_list_repo;
	FilterIterationRepo& current_dogs_repo;
	UndoRedoController& undo_redo_controller;

public:
	/// <summary>
	/// Creates a UserService
	/// </summary>
	/// <param name="all_dogs_repo"> The Repository holding all of the available dogs, represented by a reference to a Repository</param>
	/// <param name="adoption_list_repo"> The Repository holding all of the adopted dogs, represented by a reference to a Repository</param>
	/// <param name="current_dogs_repo"> The Repository holding all of the current dogs in the list to be shown</param>
	/// <param name="undo_redo_controller"> The Controller for the Undo-Redo functionality</param>
	UserService(Repository& all_dogs_repo, TextFileRepository& adoption_list_repo, FilterIterationRepo& current_dogs_repo, UndoRedoController& undo_redo_controller);

	/// <summary>
	/// Adopts a dog by deleting it from all_dogs_repo and adding it to adoption_list_repo.
	/// </summary>
	/// <param name="adopted_dog">The Dog that was adopted, represented by a reference to a Dog.</param>
	void adoptDog(DogClass::Dog& adopted_dog);

	/// <summary>
	/// Creates a vector holding all of the currently available dogs.
	/// </summary>
	/// <returns>A vector of Dogs, holding all of the available dogs.</returns>
	const std::vector<DogClass::Dog>& getAllDogs() const;
	
	/// <summary>
	/// Creates a vector holding all of the currently adopted dogs.
	/// </summary>
	/// <returns>A vector of Dogs, holding all of the adopted dogs.</returns>
	const std::vector<DogClass::Dog>& getAdoptedDogs() const;

	Dog& getCurrentDog();

	void moveToNextDog();

	void undo();

	void redo();

	void filterList(int age = -1, std::string breed = "");

	const std::string& getAdoptionListFile() const;
};
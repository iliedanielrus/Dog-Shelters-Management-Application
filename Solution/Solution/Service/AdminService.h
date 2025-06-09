#pragma once
#include "../Repository/Repository.h"
#include <string>
#include <set>
#include "../ICommand.h"
#include "../UndoRedoController.h"
class AdminService
{
private:
	Repository& repo;
	UndoRedoController& undo_redo_controller;
	
public:
	/// <summary>
	/// Creates an object of type Service
	/// </summary>
	/// <param name="repo">The Repository used to store the elements managed by the Service, represente by a reference to a Repository.</param>
	/// <param name="undo_redo_controller"> The UndoRedoController used for the undo and redo operations.
	AdminService(Repository& repo, UndoRedoController& undo_redo_controller);

	/// <summary>
	/// Adds an element to the Repository.
	/// </summary>
	/// <param name="dog"> The dog that will be added, represented by a dog reference </param>
	void addElement(const Dog& dog);

	/// <summary>
	/// Removes an element from the Repository.
	/// </summary>
	/// <param name="breed">The breed of the dog that will be removed, represented by a constant string reference.</param>
	/// <param name="name">The name of the dog that will be removed, represented by a constant string reference.</param>
	void removeElement(const std::string& breed, const std::string& name);

	/// <summary>
	/// Updates an element from the Repository
	/// </summary>
	/// <param name="old_breed">The current breed of the dog that will be updated, represented by a constant string reference.</param>
	/// <param name="old_name">The current name of the dog that will be updated, represented by a constant string reference.</param>
	/// <param name="new_dog"> The new form of the dog, represented by a dog reference </param>
	void updateElement(const std::string& old_breed, const std::string& old_name, const Dog& new_dog);

	void undo();

	void redo();

	/// <summary>
	/// Creates a vector holding all of the currently available dogs.
	/// </summary>
	/// <returns>A constant reference to a vector of Dogs, holding all of the available dogs.</returns>
	const std::vector<Dog>& getAllDogs() const;

	std::set<std::string> getDogBreeds() const;

	int getNumberOfDogsWithBreed(std::string breed) const;

	/// <summary>
	/// Adds 10 elements to the Repository.
	/// </summary>
	void add10Dogs();

};


#pragma once
#include <cstring>
#include "Repository.h"

class SQLRepoException : public std::exception
{
private:
	std::string message;

public:
	SQLRepoException(std::string message);
	const char* what() const noexcept override;
};

class SQLRepository : public Repository
{
private:
	std::string database_location;

public:
	/// <summary>
	/// Loads the elements located in the database.
	/// </summary>
	/// <throws>
	/// An SQLRepoException if the database does not exist.
	/// An SQLRepoException if the database contains elements that do not represent valid dogs (the other dogs are still added).
	/// </throws>
	void loadFromDatabase();

	/// <summary>
	/// Creates a SQLRepository.
	/// </summary>
	/// <param name="database">The location of the database, given by a string.</param>
	SQLRepository(std::string database = "");

	/// <summary>
	/// Adds an element to the repository.
	/// </summary>
	/// <param name="element">The element that will be added, represented by a constant reference to a Dog.</param>
	void addElement(const Dog& element);

	/// <summary>
	/// Deletes an element from the repository.
	/// </summary>
	/// <param name="element">The partial form of the element that will be removed, represented by a reference to an object of type Dog
	/// with the same name and breed as the searched one.</param>
	/// <returns>The dog that was removed</returns>	
	Dog removeElement(const Dog& element);

	/// <summary>
	/// Updates an element from the Repository.
	/// </summary>
	/// <param name="old_dog">The partial old form of the element, represented by an object of type Dog with the same breed and name as the searched one.</param>
	/// <param name="new_dog">The new form of the element, represented by an object of type Dog.</param>
	/// <returns>The old form of the element, represented by an object of type Dog.</returns>
	Dog updateElement(const Dog& old_dog, const Dog& new_dog);
};
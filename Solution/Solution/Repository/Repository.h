#pragma once
#include "../Domain/Dog.h"
#include <vector>
using namespace DogClass;

class RepoException : public std::exception
{
private:
	std::string message;

public:
	RepoException(std::string message);
	const char* what() const noexcept override;
};

class Repository
{
protected:
	std::vector<Dog> dog_vector;

public:
	/// <summary>
	/// Creates an object of type Repository.
	/// </summary>
	Repository();

	/// <summary>
	/// Adds an element to the Repository.
	/// </summary>
	/// <param name="element">The element to be added to the repository, represented by an object of type Dog.</param>
	/// <throws>An exception if a Dog with the same breed and name as the given one already appears in the Repository or if the Dog is not valid.</throws>
	virtual void addElement(const Dog &element);

	/// <summary>
	/// Removes an element from the Repository.
	/// </summary>
	/// <param name="element">A dog reference with the breed and name of the dog that will be deleted.</param>
	/// <returns>The removed element, represented by an object of type Dog.</returns>
	/// <throws> An exception if the Dog was not in the repository</throws>
	virtual Dog removeElement(const Dog& element);

	/// <summary>
	/// Updates an element from the Repository.
	/// </summary>
	/// <param name="old_dog">The partial old form of the element, represented by an object of type Dog with the same breed and name as the searched one.</param>
	/// <param name="new_dog">The new form of the element, represented by an object of type Dog.</param>
	/// <returns>The old form of the element, represented by an object of type Dog.</returns>
	/// <throws> 
	/// An exception if the old_dog is not found in the repository, if the Dog is not valid, 
	/// or if a Dog with the same breed and name as the new_dog already appears in the repo at another position.
	/// </throws>
	virtual Dog updateElement(const Dog& old_dog, const Dog& new_dog);

	/// <summary>
	/// Gets the position of a Dog in the Repository, looking by their unique traits, breed and name.
	/// </summary>
	/// <param name="element">The partial form of the searched dog, an object of type Dog with the same breed and name as the searched one.</param>
	/// <returns>The position of the searched dog, represented by a const_iterator, or the iterator of the end of the vector if the dog is not in the repo.</returns>
	std::vector<Dog>::const_iterator getPosition(const Dog& element) const;
	
	/// <summary>
	/// Gets a constant reference to the vector holding all of the dogs of the repo.
	/// </summary>
	/// <returns>A constant reference to the vector holding all of the dogs of the repo.</returns>
	const std::vector<Dog>& getElements() const;
	
	/// <summary>
	/// Gets the number of elements of the Repository.
	/// </summary>
	/// <returns>An integer representing the number of elements of the Repository.</returns>
	int size() const;

};

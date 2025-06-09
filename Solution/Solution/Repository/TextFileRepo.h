#pragma once
#include "Repository.h"

class TextFileRepoException : public std::exception
{
private:
	std::string message;

public:
	TextFileRepoException(std::string message);
	const char* what() const noexcept override;
};


class TextFileRepository : public Repository
{
protected:
	std::string file_location;

	/// <summary>
	/// Writes the contents of the repository to the file.
	/// </summary>
	/// <throws> A TextFileRepoException if the file does not exist. </throws>
	virtual void writeToFile();
public:
	/// <summary>
	/// Reads the contents of the repository from the file.
	/// </summary>
	/// <throws> 
	/// A TextFileRepoException if the file does not exist. 
	///	A TextFileRepoException if the file contains lines that do not represent
	/// valid dogs. (The other dogs are still added)
	/// </throws>
	virtual void loadFromFile();

	/// <summary>
	/// Creates an object of type TextFileRepository.
	/// </summary>
	/// <param name="file_location">A string representing the location of the used file.</param>
	TextFileRepository(const std::string file_location = "");

	/// <summary>
	/// Adds an element to the repository
	/// </summary>
	/// <param name="element">The element that will be added, represented by a reference to an object of type Dog.</param>
	/// <throws>An exception if a Dog with the same breed and name as the given one already appears in the Repository or if the Dog is not valid.</throws>
	void addElement(const Dog& element);

	/// <summary>
	/// Removes an element from the repository.
	/// </summary>
	/// <param name="element">The partial form of the element that will be removed, represented by a reference to an object of type Dog
	/// with the same name and breed as the searched one.</param>
	/// <returns>The dog that was removed</returns>
	/// <throws> An exception if the Dog was not in the repository</throws>
	Dog removeElement(const Dog& element);

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
	Dog updateElement(const Dog& old_dog, const Dog& new_dog);

	const std::string& getFile() const;
};
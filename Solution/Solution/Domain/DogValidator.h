#pragma once
#include "Dog.h"
#include <exception>
#include <string>

class DogException : public std::exception 
{
private:
	std::string message;

public:
	/// <summary>
	/// Creates an object of type DogException
	/// </summary>
	/// <param name="message">The message of the exception, represented by a string</param>
	DogException(std::string message);
	const char* what() const noexcept override;
};


class DogValidator
{
public:
	/// <summary>
	/// Validates an object of type Dog
	/// </summary>
	/// <param name="dog">The dog that will be validated, represented by a Dog.</param>
	static void validate(const DogClass::Dog& dog);
};

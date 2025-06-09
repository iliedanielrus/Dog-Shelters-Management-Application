#include "DogValidator.h"
#include <string>

DogException::DogException(std::string message)
{
	this->message = message;
}

const char* DogException::what() const noexcept
{
	return message.c_str();
}

void DogValidator::validate(const DogClass::Dog& dog)
{
	std::string error;
	if (dog.getBreed() == "")
		error += "The breed was not set!\n";
	if (dog.getName() == "")
		error += "The name was not set!\n";
	if (dog.getAge() < 0)
		error += "Invalid age!\n";
	if (dog.getPhotograph() == "")
		error += "The photograph was not set!\n";
	if (error != "")
		throw DogException(error);
}

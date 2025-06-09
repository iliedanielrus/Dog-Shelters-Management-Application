#include <string.h>
#include <algorithm>
#include "Repository.h"
#include "../Domain/DogValidator.h"

Repository::Repository(){}

void Repository::addElement(const Dog &element)
{
	if (this->getPosition(element) != this->dog_vector.end())
		throw RepoException("The dog was already in the list!");
	this->dog_vector.push_back(element);
}

Dog Repository::removeElement(const Dog& element)
{
	auto position = this->getPosition(element);
	if (position == this->dog_vector.end())
		throw RepoException("The dog is not in the list!");
	Dog removed_element = *position;
	this->dog_vector.erase(position);
	return removed_element;
}

Dog Repository::updateElement(const Dog& old_dog, const Dog& new_dog)
{
	auto new_elem_position = this->getPosition(new_dog);
	auto old_elem_position = this->getPosition(old_dog);
	if (new_elem_position != this->dog_vector.end() && new_elem_position != old_elem_position)
	{
		throw RepoException("The dog was already in the list on a different position!");
	}
	if (old_elem_position == this->dog_vector.end())
	{
		throw RepoException("The old element was not in the list!");
	}
	Dog old_dog_form = *old_elem_position;
	this->dog_vector[old_elem_position - this->dog_vector.begin()] = new_dog;
	return old_dog_form;
}

std::vector<Dog>::const_iterator Repository::getPosition(const Dog& element) const
{
	return find(this->dog_vector.begin(), this->dog_vector.end(), element);
}

const std::vector<Dog>& Repository::getElements() const
{
	return this->dog_vector;
}

int Repository::size() const
{
	return this->dog_vector.size();
}

RepoException::RepoException(std::string message)
{
	this->message = message;
}

const char* RepoException::what() const noexcept
{
	return this->message.c_str();
}

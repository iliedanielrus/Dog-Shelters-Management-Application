#include "FilterIterationRepo.h"

FilterIterationRepo::FilterIterationRepo()
{
	this->current_position = 0;
	this->filter_age = -1;
	this->filter_breed = "";
}

void FilterIterationRepo::setFilterBreed(std::string new_breed)
{
	this->filter_breed = new_breed;
}

void FilterIterationRepo::setFilterAge(int new_age)
{
	this->filter_age = new_age;
}

void FilterIterationRepo::filterRepo(Repository& data)
{
	this->dog_vector.clear();
	for (Dog dog : data.getElements())
		addElement(dog);
	this->current_position = 0;
}

void FilterIterationRepo::addElement(const Dog& element)
{
	if ((this->filter_breed == "" || this->filter_breed == element.getBreed()) && (this->filter_age == -1 || this->filter_age >= element.getAge()))
		Repository::addElement(element);
}

Dog& FilterIterationRepo::getElement()
{
	if (this->dog_vector.size() == 0)
		throw RepoException("No more dogs!");
	if (this->current_position >= this->dog_vector.size())
		this->current_position = 0;
	return this->dog_vector[this->current_position];
}

void FilterIterationRepo::nextElement()
{
	if (this->dog_vector.size() == 0)
		throw RepoException("No more dogs!");
	this->current_position++;
	if (this->dog_vector.size() >= this->current_position)
		this->current_position = 0;
}

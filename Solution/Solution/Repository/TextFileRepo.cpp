#include <fstream>
#include <iostream>
#include "TextFileRepo.h"
#include "../Domain/DogValidator.h"

void TextFileRepository::loadFromFile()
{
	std::ifstream read_file = std::ifstream(this->file_location);
	Dog read_dog;
	std::string unreadable = "";
	int counter = 1;
	if (read_file.is_open())
	{
		if (read_file.peek() == '\n')
			read_file.get();
		while (!read_file.eof())
		{
			try
			{
				read_file >> read_dog;
				DogValidator::validate(read_dog);
				Repository::addElement(read_dog);
			}
			catch (DogException de)
			{
				std::string temp_string;
				std::getline(read_file, temp_string);
				unreadable += std::to_string(counter);
				unreadable += " ";
			}
			counter++;
			if (read_file.peek() == '\n')
				read_file.get();
		}
		read_file.close();
		if (unreadable != "")
			throw TextFileRepoException(std::string("The lines ") + unreadable + std::string("couldn't be read!"));
	}
	else
		throw TextFileRepoException("The file does not exist!");
}

void TextFileRepository::writeToFile()
{
	std::ofstream write_file = std::ofstream(this->file_location);
	if (write_file.is_open())
	{
		for (const Dog& current_dog : this->dog_vector)
		{
			write_file << current_dog << "\n";
		}
		write_file.close();
	}
	else
		throw TextFileRepoException("The file does not exist!");
}

TextFileRepository::TextFileRepository(const std::string file_location) :Repository{}, file_location{ file_location } {}

void TextFileRepository::addElement(const Dog& element)
{
	Repository::addElement(element);
	this->writeToFile();
}

Dog TextFileRepository::removeElement(const Dog& element)
{
	Dog returning_dog = Repository::removeElement(element);
	this->writeToFile();
	return returning_dog;
}

Dog TextFileRepository::updateElement(const Dog& old_dog, const Dog& new_dog)
{
	Dog returning_dog = Repository::updateElement(old_dog, new_dog);
	this->writeToFile();
	return returning_dog;
}

const std::string& TextFileRepository::getFile() const
{
	return this->file_location;
}

TextFileRepoException::TextFileRepoException(std::string message)
{
	this->message = message;
}

const char* TextFileRepoException::what() const noexcept
{
	return this->message.c_str();
}

#include "CSVRepo.h"
#include <fstream>

CSVRepository::CSVRepository(std::string filename) :TextFileRepository{ filename } 
{
	std::ofstream write_file = std::ofstream(this->file_location);
	if (write_file.is_open())
		write_file.close();
}

void CSVRepository::writeToFile()
{
	std::ofstream write_file = std::ofstream(this->file_location);
	if (write_file.is_open())
	{
		for (const Dog& current_dog : this->dog_vector)
		{
			write_file << current_dog.getBreed() << "," << current_dog.getName() << "," << current_dog.getAge() <<"," << current_dog.getPhotograph() << "\n";
		}
		write_file.close();
	}
	else
		throw TextFileRepoException("The file does not exist!");
}

void CSVRepository::loadFromFile()
{
	throw TextFileRepoException("You can't load data from a CSV file!");
}

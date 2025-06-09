#include "HTMLRepo.h"
#include <fstream>

HTMLRepository::HTMLRepository(std::string filename) : TextFileRepository{ filename } 
{
	std::ofstream write_file = std::ofstream(this->file_location);
	if (write_file.is_open())
	{
		write_file << "<!DOCTYPE html>\n";
		write_file << "<html>\n";
		write_file << "<head>\n";
		write_file << "\t<title>Adoption list</title>\n";
		write_file << "</head>\n";
		write_file << "<body>\n";
		write_file << "<table border=\"1\">\n";
		write_file << "\t<tr>\n";
		write_file << "\t\t<td>Breed</td>\n";
		write_file << "\t\t<td>Name</td>\n";
		write_file << "\t\t<td>Age</td>\n";
		write_file << "\t\t<td>Photograph</td>\n";
		write_file << "\t</tr>\n";
		write_file << "</table>\n";
		write_file << "</body>\n";
		write_file << "</html>\n";
		write_file.close();
	}
}

void HTMLRepository::writeToFile()
{
	std::ofstream write_file = std::ofstream(this->file_location);
	if (write_file.is_open())
	{
		write_file << "<!DOCTYPE html>\n";
		write_file << "<html>\n";
		write_file << "<head>\n";
		write_file << "\t<title>Adoption list</title>\n";
		write_file << "</head>\n";
		write_file << "<body>\n";
		write_file << "<table border=\"1\">\n";
		write_file << "\t<tr>\n";
		write_file << "\t\t<td>Breed</td>\n";
		write_file << "\t\t<td>Name</td>\n";
		write_file << "\t\t<td>Age</td>\n";
		write_file << "\t\t<td>Photograph</td>\n";
		write_file << "\t</tr>\n";
		for (const Dog& current_dog : this->dog_vector)
		{
			write_file << "\t<tr>\n";
			write_file << "\t\t<td>" << current_dog.getBreed() << "</td>\n";
			write_file << "\t\t<td>" << current_dog.getName() <<"</td>\n";
			write_file << "\t\t<td>" << current_dog.getAge() <<"</td>\n";
			write_file << "\t\t<td><a href=\"" << current_dog.getPhotograph() << "\">Photograph</a></td>\n";
			write_file << "\t</tr>\n";
		}
		write_file << "</table>\n";
		write_file << "</body>\n";
		write_file << "</html>\n";
		write_file.close();
	}
	else
		throw TextFileRepoException("The file does not exist!");
}

void HTMLRepository::loadFromFile()
{
	throw TextFileRepoException("You cannot load data from a HTML repository!");
}

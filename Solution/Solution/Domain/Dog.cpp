#include "Dog.h"
#include <sstream>
#include "DogValidator.h"
namespace DogClass
{
	std::vector<std::string> Dog::splitParameters(std::string str, char delimiter)
	{
		std::vector<std::string> return_string;
		std::stringstream read_stream(str);
		std::string token;
		while (std::getline(read_stream, token, delimiter))
		{
			if (token[0] == ' ')
				token.erase(token.begin());
			if (token != "Not set!")
				return_string.push_back(token);
			else
				return_string.push_back("");
		}
		return return_string;
	}
	Dog::Dog(const std::string breed, const std::string name, int age, const std::string photograph)
	{
		this->breed = breed;
		this->name = name;
		this->age = age;
		this->photograph = photograph;
	}

	Dog::Dog(const Dog& dog)
	{
		this->breed = dog.breed;
		this->name = dog.name;
		this->age = dog.age;
		this->photograph = dog.photograph;
	}

	const std::string& Dog::getBreed() const
	{
		return this->breed;
	}

	void Dog::setBreed(const std::string& new_breed)
	{
		if (new_breed == "")
			throw DogException("Invalid breed!");
		this->breed = new_breed;
	}

	const std::string& Dog::getName() const
	{
		return this->name;
	}

	void Dog::setName(const std::string& new_name)
	{
		if (new_name == "")
			throw DogException("Invalid name!");
		this->name = new_name;
	}

	int Dog::getAge() const
	{
		return this->age;
	}

	void Dog::setAge(const int new_age)
	{
		if (new_age < 0)
			throw DogException("Invalid age!");
		this->age = new_age;
	}

	const std::string& Dog::getPhotograph() const
	{
		return this->photograph;
	}

	void Dog::setPhotograph(const std::string& new_photograph)
	{
		if (new_photograph == "")
			throw DogException("Invalid photograph!");
		this->photograph = new_photograph;
	}

	std::ostream & operator<<(std::ostream& out, const Dog& dog)
	{
		const std::string& breed = dog.getBreed();
		if(breed != "")
			out << breed;
		else
			out << "Not set!";
		out << ", ";
		const std::string& name = dog.getName();
		if (name != "")
			out << name;
		else
			out << "Not set!";
		out << ", ";
		int age = dog.getAge();
		if (age >= 0)
			out << age;
		else
			out << "Not set!";
		out << ", ";
		const std::string& link = dog.getPhotograph();
		if(link != "")
			out << link;
		else
			out << "Not set!";
		return out;
	}
	std::istream& operator>>(std::istream& in, Dog& dog)
	{
		std::string read_string;
		size_t end;
		std::getline(in, read_string);
		std::vector<std::string> tokens = dog.splitParameters(read_string, ',');
		if (tokens.size() != 4)
			throw DogException("Invalid number of parameters!");
		dog.breed = tokens[0];
		dog.name = tokens[1];
		if (tokens[2] == "")
			dog.age = -1;
		else 
		{
			try
			{
				dog.age = stoi(tokens[2], &end);
				if (end != tokens[2].size())
					throw DogException("Invalid age!");
			}
			catch (std::invalid_argument ia)
			{
				throw DogException("Invalid age!");
			}
		}
		dog.photograph = tokens[3];
		return in;
		
	}
	bool operator==(const Dog& dog1, const Dog& dog2)
	{
		return dog1.breed == dog2.breed && dog1.name == dog2.name;
	}
	bool operator!=(const Dog& dog1, const Dog& dog2)
	{
		return !(dog1 == dog2);
	}
}
#pragma once
#include <iostream>
#include <string>
#include <vector>

namespace DogClass
{
	class Dog
	{
	private:
		std::string breed;
		std::string name;
		int age;
		std::string photograph;

		/// <summary>
		/// Splits the parameters of a dog from a given string
		/// </summary>
		/// <param name="str">The string containing the parameters, represented by a string.</param>
		/// <param name="delimiter">The delimiter of the parameters, represented by a char</param>
		/// <returns>A vector of strings, containing the split string.</returns>
		static std::vector<std::string> splitParameters(std::string str, char delimiter);
	public:
		/// <summary>
		/// Creates an instance of the class Dog
		/// </summary>
		/// <param name="breed">The breed of the dog, represented by a string reference. If not given, the default value is an empty string.</param>
		/// <param name="name">The name of the dog, represented by a string reference. If not given, the default value is an empty string.</param>
		/// <param name="age">The age of the dog, represented by an integer. If not given, the default value is -1.</param>
		/// <param name="photograph">The photo of the dog given through a link, represented by a string reference. If not given, the default value is an empty string.</param>
		Dog(const std::string breed = "", const std::string name = "", int age = -1, const std::string photograph = "");

		/// <summary>
		/// Copyes an instance of the class Dog
		/// </summary>
		/// <param name="dog">The dog that will be copied, represented by an object of type Dog.</param>
		Dog(const Dog& dog);
		
		/// <summary>
		/// Gets the breed of an object of type Dog.
		/// </summary>
		/// <returns>A constant string reference representing the Dogs breed</returns>
		const std::string& getBreed() const;

		/// <summary>
		/// Sets the breed of an object of type Dog.
		/// </summary>
		/// <param name="new_breed">A constant string reference representing the Dogs new breed. Must not be an empty string.</param>
		/// <throws>An exception if the new_breed was an empty string.</throws>
		void setBreed(const std::string& new_breed);

		/// <summary>
		/// Gets the name of an object of type Dog.
		/// </summary>
		/// <returns>A constant string reference representing the Dogs name</returns>
		const std::string& getName() const;

		/// <summary>
		/// Sets the name of an object of type Dog.
		/// </summary>
		/// <param name="new_name">A constant string reference representing the Dogs new name. Must not be an empty string.</param>
		/// <throws>An exception if the new_name was an empty string.</throws>
		void setName(const std::string& new_name);

		/// <summary>
		/// Gets the age of an object of type Dog.
		/// </summary>
		/// <returns>An integer representing the Dogs age.</returns>
		int getAge() const;

		/// <summary>
		/// Sets the age of an object of type Dog.
		/// </summary>
		/// <param name="new_age">An integer representing the Dogs new age. Must be nonnegative.</param>
		/// <throws>An exception if the new_age was negative.</throws>
		void setAge(const int new_age);

		/// <summary>
		/// Gets the photograph link of an object of type Dog.
		/// </summary>
		/// <returns>A constant string reference representing the Dogs photograph link.</returns>
		const std::string& getPhotograph() const;

		/// <summary>
		/// Sets the photograph link of an object of type Dog.
		/// </summary>
		/// <param name="new_photograph">A char array representing the Dogs new photograph link. Must not be nullptr.</param>
		/// <throws>An exception if the new_photograph was an empty string.</throws>
		void setPhotograph(const std::string& new_photograph);

		/// <summary>
		/// Overloads the << operator for printing
		/// </summary>
		/// <param name="out">The stream where the dog object will be printed, represented by an object of type ostream.</param>
		/// <param name="dog">The dog that will be printed, represented by an object of type Dog.</param>
		/// <returns>The stream where the dog was printed.</returns>
		friend std::ostream & operator<<(std::ostream& out, const Dog& dog);

		/// <summary>
		/// Overloads the >> operator for reading
		/// </summary>
		/// <param name="in">The stream from where the dog object will be read, represented by an object of type istream.</param>
		/// <param name="dog">The dog that will be read, represented by an object of type Dog.</param>
		/// <returns>The stream from where the dog was read.</returns>
		friend std::istream& operator>>(std::istream& in, Dog& dog);

		/// <summary>
		/// Overloades the == operator
		/// </summary>
		/// <param name="dog1">The first dog of the comparison, represented by an object of type Dog</param>
		/// <param name="dog2">The second dog of the comparison, represented by an object of type Dog</param>
		/// <returns>True if both dogs have the same breed and name, otherwise false</returns>
		friend bool operator==(const Dog& dog1, const Dog& dog2);

		/// <summary>
		/// Overloades the != operator
		/// </summary>
		/// <param name="dog1">The first dog of the comparison, represented by an object of type Dog</param>
		/// <param name="dog2">The second dog of the comparison, represented by an object of type Dog</param>
		/// <returns>False if both dogs have the same breed and name, otherwise true</returns>
		friend bool operator!=(const Dog& dog1, const Dog& dog2);
	};
}

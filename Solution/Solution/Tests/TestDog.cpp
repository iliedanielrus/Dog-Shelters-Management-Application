#include "TestDog.h"
#include "../Domain/Dog.h"
#include <cassert>
#include <sstream>
#include "../Domain/DogValidator.h"

using namespace DogClass;

void testCreateDog()
{
	Dog dog = Dog("Teckel", "Georgie", 12, "www");
	std::string breed = dog.getBreed(), name = dog.getName(), link = dog.getPhotograph();
	assert(breed == "Teckel");
	assert(name == "Georgie");
	assert(dog.getAge() == 12);
	assert(link == "www");
	Dog copy_dog = Dog(dog);
	breed = copy_dog.getBreed();
	name = copy_dog.getName();
	link = copy_dog.getPhotograph();
	assert(breed == "Teckel");
	assert(name == "Georgie");
	assert(copy_dog.getAge() == 12);
	assert(link == "www");
	Dog empty_dog = Dog(), empty_copy_dog = Dog(empty_dog);
	assert(empty_copy_dog.getBreed() == "");
	assert(empty_copy_dog.getName() == "");
	assert(empty_copy_dog.getAge() == -1);
	assert(empty_copy_dog.getPhotograph() == ""); 
}

void testOperatorAssign()
{
	Dog dog = Dog("Teckel", "Georgie", 12, "www"), other_dog;
	other_dog = dog;
	std::string breed = other_dog.getBreed(), name = other_dog.getName(), link = other_dog.getPhotograph();
	assert(breed == "Teckel");
	assert(name == "Georgie");
	assert(other_dog.getAge() == 12);
	assert(link == "www");
	Dog empty_dog = Dog(), copy_empty_dog;
	copy_empty_dog = empty_dog;
	assert(copy_empty_dog.getBreed() == "");
	assert(copy_empty_dog.getName() == "");
	assert(copy_empty_dog.getAge() == -1);
	assert(copy_empty_dog.getPhotograph() == "");
}

void testGetBreed()
{
	Dog dog = Dog();
	assert(dog.getBreed() == "");
	Dog other_dog = Dog("Teckel", "Georgie", 12, "www");
	std::string breed = other_dog.getBreed();
	assert(breed == "Teckel");
}

void testSetBreed()
{
	Dog dog = Dog();
	try { dog.setBreed(""); assert(false); }
	catch (DogException de) { assert(strcmp(de.what(), "Invalid breed!") == 0); }
	dog.setBreed("Corgi");
	std::string breed = dog.getBreed();
	assert(breed == "Corgi");
}

void testGetName()
{
	Dog dog = Dog();
	assert(dog.getName() == "");
	Dog other_dog = Dog("Teckel", "Georgie", 12, "www");
	std::string name = other_dog.getName();
	assert(name == "Georgie");
}

void testSetName()
{
	Dog dog = Dog();
	try { dog.setName(""); assert(false); }
	catch (DogException de) { assert(strcmp(de.what(), "Invalid name!") == 0); }
	dog.setName("Rex");
	std::string name = dog.getName();
	assert(name == "Rex");
}

void testGetAge()
{
	Dog dog = Dog();
	assert(dog.getAge() == -1);
	Dog other_dog = Dog("Teckel", "Georgie", 12, "www");
	assert(other_dog.getAge() == 12);
}

void testSetAge()
{
	Dog dog = Dog();
	try { dog.setAge(-1); assert(false); }
	catch (DogException de) { assert(strcmp(de.what(), "Invalid age!") == 0); }
	dog.setAge(13);
	assert(dog.getAge() == 13);
}

void testGetPhotograph()
{
	Dog dog = Dog();
	assert(dog.getPhotograph() == "");
	Dog other_dog = Dog("Teckel", "Georgie", 12, "www");
	std::string link = other_dog.getPhotograph();
	assert(link == "www");
}

void testSetPhotograph()
{
	Dog dog = Dog();
	try { dog.setPhotograph(""); assert(false); }
	catch (DogException de) { assert(strcmp(de.what(), "Invalid photograph!") == 0); }
	dog.setPhotograph("www");
	std::string link = dog.getPhotograph();
	assert(link == "www");
}

void testOperatorInsertion()
{
	Dog dog = Dog("A", "B", 1, "C"), other_dog = Dog();
	std::ostringstream out, out_2;
	out << dog;
	out_2 << other_dog;
	assert(out.str() == "A, B, 1, C");
	assert(out_2.str() == "Not set!, Not set!, Not set!, Not set!");
}

void testOperatorExtraction()
{
	std::string str1("x, y, Not set!, z"), str2("x, y, z, t"), str3("x, y, 2, t"), str4("x, y"), str5("x, y, 2z, t");
	std::istringstream in_1(str1), in_2(str2), in_3(str3), in_4(str4), in_5(str5);
	Dog dog;
	in_1 >> dog;
	assert(dog.getBreed() == "x");
	assert(dog.getName() == "y");
	assert(dog.getAge() == -1);
	assert(dog.getPhotograph() == "z");
	try { in_2 >> dog; assert(false); }
	catch (DogException de) { assert(strcmp(de.what(), "Invalid age!") == 0); }
	in_3 >> dog;
	assert(dog.getBreed() == "x");
	assert(dog.getName() == "y");
	assert(dog.getAge() == 2);
	assert(dog.getPhotograph() == "t");
	try { in_4 >> dog; assert(false); }
	catch (DogException de) { assert(strcmp(de.what(), "Invalid number of parameters!") == 0); }
	try { in_5 >> dog; assert(false); }
	catch (DogException de) { assert(strcmp(de.what(), "Invalid age!") == 0); }

}

void testValidate()
{
	Dog dog1 = Dog(), dog2 = Dog("name"), dog3 = Dog("A", "B"), dog4 = Dog("A", "B", 1), dog5 = Dog("A", "B", 1, "C");
	try { DogValidator::validate(dog1); assert(false); }
	catch (DogException de) { assert(strcmp(de.what(), "The breed was not set!\nThe name was not set!\nInvalid age!\nThe photograph was not set!\n") == 0); }
	try { DogValidator::validate(dog2); assert(false); }
	catch (DogException de) { assert(strcmp(de.what(), "The name was not set!\nInvalid age!\nThe photograph was not set!\n") == 0); }
	try { DogValidator::validate(dog3); assert(false); }
	catch (DogException de) { assert(strcmp(de.what(), "Invalid age!\nThe photograph was not set!\n") == 0); }
	try { DogValidator::validate(dog4); assert(false); }
	catch (DogException de) { assert(strcmp(de.what(), "The photograph was not set!\n") == 0); }
	DogValidator::validate(dog5);
}

void testOperatorEquals()
{
	Dog dog1 = Dog("A", "B", 1, "C"), dog2 = Dog("A", "B", 2, "C"), dog3 = Dog("A", "C", 1, "C");
	assert(dog1 == dog2);
	assert(!(dog1 == dog3));
}

void testOperatorNotEquals()
{
	Dog dog1 = Dog("A", "B", 1, "C"), dog2 = Dog("A", "B", 2, "C"), dog3 = Dog("A", "C", 1, "C");
	assert(!(dog1 != dog2));
	assert(dog1 != dog3);
}


void testAllDog()
{
	testCreateDog();
	testOperatorAssign();
	testGetBreed();
	testSetBreed();
	testGetName();
	testSetName();
	testGetAge();
	testSetAge();
	testGetPhotograph();
	testSetPhotograph();
	testOperatorInsertion();
	testOperatorExtraction();
	testValidate();
	testOperatorEquals();
	testOperatorNotEquals();
}

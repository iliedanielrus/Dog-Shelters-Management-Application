#include <assert.h>
#include "TestUserService.h"
#include "../Domain/Dog.h"
#include "../Repository/Repository.h"
#include "../Repository/TextFileRepo.h"
#include "../Service/UserService.h"

void testCreateUserService()
{
	Repository all_repo = Repository();
	TextFileRepository adopted_repo = TextFileRepository();
	UserService serv = UserService(all_repo, adopted_repo);
}

void testAdoptDog()
{
	Repository all_repo = Repository();
	TextFileRepository adopted_repo = TextFileRepository("test_user_service_file.txt");
	UserService serv = UserService(all_repo, adopted_repo);
	DogClass::Dog test_null_dog = Dog(), test_dog = Dog("A", "B", 1, "C");
	all_repo.addElement(test_dog);
	try { serv.adoptDog(test_null_dog); assert(false); }
	catch (RepoException re) { assert(strcmp(re.what(), "The dog is not in the list!") == 0); }
	serv.adoptDog(test_dog);
	assert(all_repo.size() == 0);
	assert(adopted_repo.size() == 1);
	assert(adopted_repo.getPosition(test_dog) == adopted_repo.getElements().begin());
}

void testGetAllDogs()
{
	Repository all_repo = Repository();
	TextFileRepository adopted_repo = TextFileRepository("test_user_service_file.txt");	
	UserService serv = UserService(all_repo, adopted_repo);
	DogClass::Dog test_dog = Dog("A", "B", 1, "C");
	all_repo.addElement(test_dog);
	std::vector<DogClass::Dog> da3 = serv.getAllDogs();
	assert(da3.size() == 1);
	DogClass::Dog test_dog2 = *da3.begin();
	std::string breed = test_dog2.getBreed(), name = test_dog2.getName(), link = test_dog2.getPhotograph();
	assert(breed == "A");
	assert(name == "B");
	assert(test_dog2.getAge() == 1);
	assert(link == "C");
}

void testGetFilteredDogs()
{
	Repository all_repo = Repository();
	TextFileRepository adopted_repo = TextFileRepository("test_user_service_file.txt");	
	UserService serv = UserService(all_repo, adopted_repo);
	DogClass::Dog test_dog1 = Dog("A", "B", 1, "C"), test_dog2 = Dog("A", "D", 2, "E"), test_dog3 = Dog("F", "G", 1, "H");
	all_repo.addElement(test_dog1);
	all_repo.addElement(test_dog2);
	all_repo.addElement(test_dog3);
	std::vector<DogClass::Dog> da3 = serv.getFilteredDogs("A", 2);
	assert(da3.size() == 1);
	DogClass::Dog test_dog4 = *da3.begin();
	std::string breed = test_dog4.getBreed(), name = test_dog4.getName(), link = test_dog4.getPhotograph();
	assert(breed == "A");
	assert(name == "B");
	assert(test_dog4.getAge() == 1);
	assert(link == "C");
}

void testGetAdoptedDogs()
{
	Repository all_repo = Repository();
	TextFileRepository adopted_repo = TextFileRepository("test_user_service_file.txt");	
	UserService serv = UserService(all_repo, adopted_repo);
	DogClass::Dog test_dog = Dog("A", "B", 1, "C"), test_dog2 = Dog("A", "C", 2, "D");
	all_repo.addElement(test_dog);
	all_repo.addElement(test_dog2);
	serv.adoptDog(test_dog2);
	std::vector<DogClass::Dog> da3 = serv.getAdoptedDogs();
	assert(da3.size() == 1);
	DogClass::Dog test_dog3 = *da3.begin();
	std::string breed = test_dog3.getBreed(), name = test_dog3.getName(), link = test_dog3.getPhotograph();
	assert(breed == "A");
	assert(name == "C");
	assert(test_dog2.getAge() == 2);
	assert(link == "D");
}

void testAllUserService()
{
	testCreateUserService();
	testAdoptDog();
	testGetAllDogs();
	testGetFilteredDogs();
	testGetAdoptedDogs();
}

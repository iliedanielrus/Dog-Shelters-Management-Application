#include <assert.h>
#include <string>
#include "TestAdminService.h"
#include "../Domain/Dog.h"
#include "../Repository/Repository.h"
#include "../Service/AdminService.h"
#include "../Domain/DogValidator.h"

void testCreateAdminService()
{
	Repository repo = Repository();
	AdminService serv = AdminService(repo);
}
\
void testAddElementAdminService()
{
	Repository repo = Repository();
	AdminService serv = AdminService(repo);
	serv.addElement(Dog("Teckel", "Georgie", 12, "www"));
	try { serv.addElement(Dog("Teckel", "Georgie", -1, "yyy")); assert(false); }
	catch (DogException de) { assert(strcmp(de.what(), "Invalid age!\n") == 0); }
	Dog search_dog = Dog("Teckel", "Georgie");
	assert(repo.getPosition(search_dog) != repo.getElements().end());
}

void testRemoveElementAdminService()
{
	Repository repo = Repository();
	AdminService serv = AdminService(repo);
	serv.addElement(Dog("Teckel", "Georgie", 12, "www"));
	try { serv.removeElement("A", "B"); assert(false); }
	catch (RepoException re) { assert(strcmp(re.what(), "The dog is not in the list!") == 0); }
	DogClass::Dog removed_dog = serv.removeElement("Teckel", "Georgie");
	assert(repo.size() == 0);
	std::string breed = removed_dog.getBreed(), name = removed_dog.getName();
	assert(breed == "Teckel");
	assert(name == "Georgie");
}

void testUpdateElementAdminService()
{
	Repository repo = Repository();
	AdminService serv = AdminService(repo);
	serv.addElement(Dog("Teckel", "Georgie", 12, "www"));
	try { serv.updateElement("A", "B", Dog("A", "B", 2, "D")); assert(false); }
	catch (RepoException re) { assert(strcmp(re.what(), "The old element was not in the list!") == 0); }
	DogClass::Dog removed_dog = serv.updateElement("Teckel", "Georgie", Dog("A", "B", 2, "D"));
	assert(repo.size() == 1);
	std::string breed = removed_dog.getBreed(), name = removed_dog.getName();
	assert(breed == "Teckel");
	assert(name == "Georgie");
	Dog search_dog = Dog("A", "B");
	assert(repo.getPosition(search_dog) != repo.getElements().end());
}


void testAdd10DogsAdminService()
{
	Repository repo = Repository();
	AdminService serv = AdminService(repo);
	serv.add10Dogs();
	assert(repo.size() == 10);
}

void testGetAllDogsAdmin()
{
	Repository repo = Repository();
	AdminService serv = AdminService(repo);
	serv.addElement(Dog("Teckel", "Georgie", 12, "www"));
	serv.addElement(Dog("A", "B", 1, "www"));
	std::vector<DogClass::Dog> test_vector = serv.getAllDogs();
	assert(test_vector.size() == 2);
	assert(*(test_vector.begin()) == Dog("Teckel", "Georgie"));
	assert(*(test_vector.begin()+1) == Dog("A", "B"));
}

void testAllAdminService()
{
	testCreateAdminService();
	testAddElementAdminService();
	testRemoveElementAdminService();
	testUpdateElementAdminService();
	testAdd10DogsAdminService();
	testGetAllDogsAdmin();
}

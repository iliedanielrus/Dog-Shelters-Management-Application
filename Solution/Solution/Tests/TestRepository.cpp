#include <assert.h>
#include "TestRepository.h"
#include "../Domain/Dog.h"
#include "../Repository/Repository.h"

void testCreateRepository()
{
	Repository repo = Repository();
	assert(repo.size() == 0);
}

void testAddElementRepository()
{
	Repository repo = Repository();
	DogClass::Dog test_dog_good = Dog("Teckel", "Georgie", 12, "WWW"), test_dog_copy = Dog(test_dog_good);
	repo.addElement(test_dog_good);
	DogClass::Dog test_search_dog = Dog("Teckel", "Georgie");
	assert(repo.getPosition(test_search_dog) != repo.getElements().end());
	try { repo.addElement(test_dog_copy); assert(false); }
	catch (RepoException re) { assert(strcmp(re.what(), "The dog was already in the list!") == 0); }
}

void testRemoveElementRepository()
{
	Repository repo = Repository();
	DogClass::Dog test_dog_1 = Dog("Teckel", "Georgie", 12, "WWW"), test_dog_2 = Dog("A", "B", 1, "D");
	repo.addElement(test_dog_1);
	repo.addElement(test_dog_2);
	Dog removed_dog = repo.removeElement(test_dog_1);
	std::string breed = removed_dog.getBreed(), name = removed_dog.getName();
	assert(breed == "Teckel");
	assert(name == "Georgie");
	assert(repo.size() == 1);
}

void testUpdateElementRepository()
{
	Repository repo = Repository();
	DogClass::Dog test_dog_1 = Dog("Teckel", "Georgie", 12, "WWW"), test_dog_2 = Dog("A", "B", 1, "D");
	repo.addElement(test_dog_1);
	Dog removed_dog = repo.updateElement(test_dog_1, test_dog_2);
	std::string breed = removed_dog.getBreed(),  name = removed_dog.getName();
	assert(breed == "Teckel");
	assert(name == "Georgie");
	assert(repo.size() == 1);
	assert(repo.getPosition(test_dog_2) == repo.getElements().begin());
	repo.addElement(test_dog_1);
	try { repo.updateElement(test_dog_1, test_dog_2); assert(false); }
	catch (RepoException re) { assert(strcmp(re.what(), "The dog was already in the list on a different position!") == 0); }
}

void testGetPositionRepository()
{
	Repository repo = Repository();
	DogClass::Dog test_dog_1 = Dog("Teckel", "Georgie", 12, "WWW"), test_dog_2 = Dog("A", "B", 1, "D"), test_dog_3 = Dog("A", "C");
	repo.addElement(test_dog_1);
	repo.addElement(test_dog_2);
	assert(repo.getPosition(test_dog_1) == repo.getElements().begin());
	assert(repo.getPosition(test_dog_2) == repo.getElements().begin()+1);
	assert(repo.getPosition(test_dog_3) == repo.getElements().end());
}

void testSizeRepository()
{
	Repository repo = Repository();
	DogClass::Dog test_dog_1 = Dog("Teckel", "Georgie", 12, "WWW");
	assert(repo.size() == 0);
	repo.addElement(test_dog_1);
	assert(repo.size() == 1);
}


void testAllRepository()
{
	testCreateRepository();
	testAddElementRepository();
	testRemoveElementRepository();
	testUpdateElementRepository();
	testGetPositionRepository();
	testSizeRepository();
}

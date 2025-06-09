#include "TestTextFileRepo.h"
#include "../Repository/TextFileRepo.h"
#include <cassert>
#include <fstream>

void testCreateTextFileRepo()
{
	TextFileRepository repo = TextFileRepository("test_file.txt");
}

void testLoadFromFile()
{
	TextFileRepository repo_broken("nonexistent_file.txt"), repo_test("Tests/test_file.txt");
	try { repo_broken.loadFromFile(); assert(false); }
	catch (TextFileRepoException tfre) { assert(strcmp(tfre.what(), "The file does not exist!") == 0); }
	try { repo_test.loadFromFile(); assert(false); }
	catch (TextFileRepoException tfre) { assert(strcmp(tfre.what(), "The lines 3 couldn't be read!") == 0); }
	assert(repo_test.size() == 2);
}

void testAddTextFileRepo()
{
	TextFileRepository repo_test("Tests/test_file_good.txt");
	repo_test.loadFromFile();
	Dog test_dog("A", "D", 4, "E");
	repo_test.addElement(test_dog);
	assert(repo_test.size() == 3);
	std::ifstream fin_test("Tests/test_file_good.txt");
	std::string test_string;
	std::getline(fin_test, test_string);
	assert(test_string == "A, B, 2, D");
	std::getline(fin_test, test_string);
	assert(test_string == "A, C, 3, D");
	std::getline(fin_test, test_string);
	assert(test_string == "A, D, 4, E");
	fin_test.close();
}

void testUpdateTextFileRepo()
{
	TextFileRepository repo_test("Tests/test_file_good.txt");
	repo_test.loadFromFile();
	Dog test_dog("A", "D", 4, "E"), test_replacement("B", "C", 2, "G");
	repo_test.updateElement(test_dog, test_replacement);
	assert(repo_test.size() == 3);
	std::ifstream fin_test("Tests/test_file_good.txt");
	std::string test_string;
	std::getline(fin_test, test_string);
	assert(test_string == "A, B, 2, D");
	std::getline(fin_test, test_string);
	assert(test_string == "A, C, 3, D");
	std::getline(fin_test, test_string);
	assert(test_string == "B, C, 2, G");
	fin_test.close();
}

void testRemoveTextFileRepo()
{
	TextFileRepository repo_test("Tests/test_file_good.txt");
	repo_test.loadFromFile();
	Dog test_dog("B", "C", 2, "G");
	repo_test.removeElement(test_dog);
	assert(repo_test.size() == 2);
	std::ifstream fin_test("Tests/test_file_good.txt");
	std::string test_string;
	std::getline(fin_test, test_string);
	assert(test_string == "A, B, 2, D");
	std::getline(fin_test, test_string);
	assert(test_string == "A, C, 3, D");
	fin_test.close();
}

void testAllTextFileRepo()
{
	testCreateTextFileRepo();
	testLoadFromFile();
	testAddTextFileRepo();
	testUpdateTextFileRepo();
	testRemoveTextFileRepo();
}

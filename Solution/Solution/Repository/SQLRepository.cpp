#include "../sqlite3.h"
#include <sstream>
#include "SQLRepository.h"
#include "../Domain/DogValidator.h"

void SQLRepository::loadFromDatabase()
{
	sqlite3* database;
	int rc, row = 1;
	bool done = false;
	std::string dog_string, err_string="";
	std::stringstream dog_stream;
	Dog current_dog;
	rc = sqlite3_open(this->database_location.c_str(), &database);
	if (rc)
		throw SQLRepoException("Cannot open database!");
	std::string sql;
	sql = "SELECT * FROM DOGLIST";
	sqlite3_stmt* stmt;
	sqlite3_prepare_v2(database, sql.c_str(), sql.size(), &stmt, nullptr);
	while (!done)
	{
		switch (sqlite3_step(stmt)) 
		{
		case SQLITE_ROW:
			dog_string = "";
			dog_string += std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0))) + ", ";
			dog_string += std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1))) + ", ";
			dog_string += std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2))) + ", ";
			dog_string += std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
			dog_stream = std::stringstream(dog_string);
			try
			{
				dog_stream >> current_dog;
				DogValidator::validate(current_dog);
				Repository::addElement(current_dog);
			}
			catch (DogException de)
			{
				err_string += std::to_string(row);
				err_string += " ";
			}
			row++;
			break;

		case SQLITE_DONE:
			done = true;
			break;
		}
	}
	sqlite3_finalize(stmt);
	sqlite3_close(database);
	if (err_string != "")
		throw SQLRepoException("The lines " + err_string + " are unreadable!");
}

SQLRepository::SQLRepository(std::string database) : Repository{}
{
	this->database_location = database;
}

void SQLRepository::addElement(const Dog& element)
{
	Repository::addElement(element);
	sqlite3* database;
	int rc;
	rc = sqlite3_open(this->database_location.c_str(), &database);
	if (rc)
		throw SQLRepoException("Cannot open database!");
	std::string sql;
	sql = "INSERT INTO DOGLIST (BREED, NAME, AGE, PHOTOGRAPH) VALUES ('" + element.getBreed() + "', '" 
		+ element.getName() + "', " + std::to_string(element.getAge()) + ", '" + element.getPhotograph() + "');";
	rc = sqlite3_exec(database, sql.c_str(), nullptr, nullptr, nullptr);
	sqlite3_close(database);
	if (rc != SQLITE_OK)
		throw SQLRepoException("Error in addition to database!");
}

Dog SQLRepository::removeElement(const Dog& element)
{
	Dog returning_dog = Repository::removeElement(element);
	sqlite3* database;
	int rc;
	rc = sqlite3_open(this->database_location.c_str(), &database);
	if (rc)
		throw SQLRepoException("Cannot open database!");
	std::string sql;
	sql = "DELETE from DOGLIST where BREED = '" + element.getBreed() + "' AND NAME = '" + element.getName() + "';";
	rc = sqlite3_exec(database, sql.c_str(), nullptr, nullptr, nullptr);
	sqlite3_close(database);
	if (rc != SQLITE_OK)
		throw SQLRepoException("Error in deletion from database!");
	return returning_dog;
}

Dog SQLRepository::updateElement(const Dog& old_dog, const Dog& new_dog)
{
	Dog returning_dog = Repository::updateElement(old_dog, new_dog);
	sqlite3* database;
	int rc;
	rc = sqlite3_open(this->database_location.c_str(), &database);
	if (rc)
		throw SQLRepoException("Cannot open database!");
	std::string sql;
	sql = "UPDATE DOGLIST set BREED = '" + new_dog.getBreed() + "', NAME = '" + new_dog.getName() + "', AGE = " + std::to_string(new_dog.getAge()) + ", PHOTOGRAPH = '" 
		+ new_dog.getPhotograph() + "' WHERE BREED = '" + old_dog.getBreed() + "' AND NAME = '" + old_dog.getName() + "';";
	rc = sqlite3_exec(database, sql.c_str(), nullptr, nullptr, nullptr);
	sqlite3_close(database);
	if (rc != SQLITE_OK)
		throw SQLRepoException("Error in update");
	return returning_dog;
}

SQLRepoException::SQLRepoException(std::string message)
{
	this->message = message;
}

const char* SQLRepoException::what() const noexcept
{
	return this->message.c_str();
}

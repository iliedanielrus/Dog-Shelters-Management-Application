#pragma once
#include "Repository/Repository.h"
class FilterIterationRepo : public Repository
{
private:
	std::string filter_breed;
	int filter_age, current_position;

public:
	FilterIterationRepo();
	void setFilterBreed(std::string new_breed);
	void setFilterAge(int new_age);
	void filterRepo(Repository& data);
	void addElement(const Dog& element) override;
	Dog& getElement();
	void nextElement();
};


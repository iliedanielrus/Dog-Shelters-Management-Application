#pragma once
#include "TextFileRepo.h"

class CSVRepository : public TextFileRepository
{
private:
	/// <summary>
	/// Writes the current contents of the Repository in the file using CSV formatting.
	/// </summary>
	void writeToFile();

public:
	/// <summary>
	/// Creates a CSVRepository
	/// </summary>
	/// <param name="filename">The name of the file, represented by a string.</param>
	CSVRepository(std::string filename);

	/// <summary>
	/// Raises a TextFileRepository, since data shouldn't be read from the CSV file.
	/// </summary>
	void loadFromFile();
};
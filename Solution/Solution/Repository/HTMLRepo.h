#pragma once
#include "TextFileRepo.h"

class HTMLRepository : public TextFileRepository
{
private:
	/// <summary>
	/// Writes the current contents of the Repository in the file using HTML formatting.
	/// </summary>
	void writeToFile();

public:
	/// <summary>
	/// Creates a HTMLRepository
	/// </summary>
	/// <param name="filename">The name of the file, represented by a string.</param>
	HTMLRepository(std::string filename);

	/// <summary>
	/// Raises a TextFileRepository, since data shouldn't be read from the HTML file.
	/// </summary>
	void loadFromFile();
};
#include <iostream>

#include "World.h"

template <size_t ColumnNumber> std::vector<std::array<std::string, ColumnNumber>> parseCSV(std::string filePath)
{
	std::vector<std::array<std::string, ColumnNumber>> output;

	// File pointer 
	std::ifstream fin;

	// Open an existing file 
	fin.open(filePath);

	// Read the Data from the file 
	// as String Vector 
	std::vector<std::string> row;
	std::string line, word, temp;

	if (!fin.is_open())
	{
		// error message system here 
		return output;
	}

	while (std::getline(fin, line)) {

		std::array<std::string, ColumnNumber> row;
		row.fill("");

		// used for breaking words 
		std::istringstream ss(line);

		int i = 0;
		// getline only continues if there is still something to parse
		while (i < ColumnNumber && std::getline(ss, word, ';')) {
			std::cout << word << std::endl;

			// is this inefficent? should the getline write into the array index immediatley?
			row[i] = word;
			i++;
		}

		output.push_back(std::move(row));
	}

	return output;
}

int main() {	
	World myCoolWorld;
    myCoolWorld.Init();

    while (myCoolWorld.m_generation < 10000)
    {

        myCoolWorld.Tick();
        myCoolWorld.Evolve();
	}

    myCoolWorld.Fini();

    getchar();
	system("python3 Visualize.py");
	return 0;
}


#include "Upload.h"
#include <fstream>
#include <sstream>

Upload::Upload(int size, std::string structure_choice) : size(size), structure_choice(structure_choice)
{
	this->size = size;
	dataFromFile();
}

void Upload::dataFromFile()
{
	std::ifstream file;
	file.open("recipes.csv");

	if (file.is_open())
	{
		// Read each line from the file
		std::string line;
		std::getline(file, line);
		if (structure_choice == "tree")
		{
			rbTree = new RB_Tree<Recipes>;
			while (std::getline(file, line))
			{
				if (size != 0)
					if (rbTree->getSize() >= size) break;

				std::stringstream ss(line);
				std::string name, idStr, minutesStr;

				// Extract name, id, and minutes from the line
				if (std::getline(ss, name, ',') && std::getline(ss, idStr, ',') && std::getline(ss, minutesStr, ','))
				{
					Recipes recipes;
					recipes.name = name;
					recipes.index = std::stoi(idStr);
					recipes.value = std::stoi(minutesStr);

					rbTree->insert(recipes);
				}
			}
		}
		if (structure_choice == "HashMap")
		{
			while (std::getline(file, line))
			{
				if (size != 0)
					if (hashMap.getSize() >= size) break;

				std::stringstream ss(line);
				std::string name, idStr, minutesStr;

				// Extract name, id, and minutes from the line
				if (std::getline(ss, name, ',') && std::getline(ss, idStr, ',') && std::getline(ss, minutesStr, ','))
				{
					Recipes recipes;
					recipes.name = name;
					recipes.index = std::stoi(idStr);
					recipes.value = std::stoi(minutesStr);

					hashMap.insert(recipes.name, recipes);
				}
			}
		}
		if (structure_choice == "HashTable")
		{
			if (size == 0)
			{
				// Calculate the size based on the number of entries in the file
				size = 0;
				while (std::getline(file, line))
				{
					size++;
				}
				file.clear();    // Reset the file stream
				file.seekg(0);   // Move the file pointer back to the beginning
				std::getline(file, line);  // Skip the header line
			}
			hashTable = new HashTable<std::string, Recipes>(size);
			while (std::getline(file, line))
			{
				if (size == 0)
					break;

				std::stringstream ss(line);
				std::string name, idStr, minutesStr;

				// Extract name, id, and minutes from the line
				if (std::getline(ss, name, ',') && std::getline(ss, idStr, ',') && std::getline(ss, minutesStr, ','))
				{
					Recipes recipes;
					recipes.name = name;
					recipes.index = std::stoi(idStr);
					recipes.value = std::stoi(minutesStr);

					hashTable->insert(recipes.name, recipes);
				}
				size--;

			}
		}
	}

	file.close();
}

std::vector<typename RB_Tree<Recipes>::Node_p> Upload::findInTree(int value)
{
	return rbTree->find(value);
}

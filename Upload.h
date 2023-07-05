#pragma once
#include <string>
#include "RB_Tree.h"
#include "HashMap.h"
#include "HashTable.h"

struct Recipes
{
	int index;		  // id
	std::string name; // name
	int value;		  // minutes
};

class Upload
{
protected:
		int size;
		std::string structure_choice;

public:
	RB_Tree<Recipes>* rbTree = new RB_Tree<Recipes>;
	HashMap<std::string, Recipes> hashMap;
	HashTable<std::string, Recipes>* hashTable ;

	Upload(int size, std::string structure_choice);//, std::string structure_choice);

	void dataFromFile();
	std::vector<typename RB_Tree<Recipes>::Node_p> findInTree(int value);
};

#include "Upload.cpp"
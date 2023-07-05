#include "RB_Tree.h"
#include "HashTable.h"
#include "HashTable.cpp"
#include "HashMap.h"
#include "Upload.h"
#include "time_measure.h"
#include <iostream>
#include <fstream>

void saveVariableToFile(const double & variable, const int& count, const std::string& filePath)
{
    std::ofstream file(filePath, std::ios::app);
    if (file.is_open()) {
        file << variable << "\n";
        file.close();
    }
}

std::string* loadFirstColumnFromCSV(const std::string& filePath, int numElements) {
    std::ifstream file(filePath);
    if (file.is_open()) {
        std::string line;
        std::string* firstColumn = new std::string[numElements+1];

        for (int i = 0; i < numElements+1; ++i) {
            if (!std::getline(file, line)) {
                std::cout << "File does not have enough lines." << std::endl;
                delete[] firstColumn;
                return nullptr;
            }

            std::istringstream iss(line);
            std::getline(iss, firstColumn[i], ',');
        }

        file.close();
        std::cout << "First column loaded from file successfully." << std::endl;
        return firstColumn;
    }
    else {
        std::cout << "Unable to open file for reading." << std::endl;
        return nullptr;
    }
}
int main()
{
    
    int maxim = 231637;
    int number_elements = 100;
    double start, end, time;
    //std::string* firstColumn = loadFirstColumnFromCSV("recipes.csv", number_elements);
    //start = get_wall_time();
    //Upload *upload = new Upload(0, "tree");
    //end = get_wall_time();

    /*
    start = get_wall_time();
    Upload upload_hash = Upload(number_elements, "HashMap");
    end = get_wall_time();

    start = get_wall_time();
    for (int i = 1; i < number_elements+1; i++)
    {
        //upload_hash.hashMap.remove(firstColumn[i]);
        Recipes zmienna = upload_hash.hashMap.get(firstColumn[i]);
    }
    end = get_wall_time();
    */

    /*
    start = get_wall_time();
    Upload *upload_table = new Upload(number_elements, "HashTable");
    end = get_wall_time();
    start = get_wall_time();
    for (int i = 1; i < number_elements + 1; i++)
    {
        //upload_table->hashTable->remove(firstColumn[i]);
        //Recipes zmienna = upload_table ->hashTable ->get(firstColumn[i]);
    }
    end = get_wall_time();
    //upload->rbTree->show();
    */

    
    /*Recipes zmienna =  upload_table->hashTable->get("20 000 prize winning chili con carne");
    
    std::cout << zmienna.name << zmienna.index << std::endl;
    std::cout << end - start << std::endl;*/

    //upload->rbTree->find(105);


    Upload* upload = new Upload(160000, "tree");
    
    //int height = upload->rbTree->height();
    //upload->rbTree->show();
    start = get_wall_time();
    std::vector<typename RB_Tree<Recipes>::Node_p> result = upload->findInTree(2147483647);
    end = get_wall_time();
    //std::cout << "Job done : "<< height << std::endl;


    time = end - start;

    saveVariableToFile(time, number_elements, "tree_find.txt");
}
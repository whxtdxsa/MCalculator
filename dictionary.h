#pragma once
#include <fstream>
#include <sstream>

#include "dim.h"

class Dictionary {
private:
    int* s_num_;     // Info of the number of structure type
    std::string** dictionary_;  // Dictionary

public:
    Dictionary();   // Allocate memory
    ~Dictionary();  // Release memory

    int dictionaryPull(std::string _file);  // Make dictionary from 'dictionary.txt'

    int* getSNum();       // Get memberdata
    std::string** getDictionary();  // Get memberdata

    int IdToOrder(int _id);
    int IdToDim(int _id);        // Check the kind of dimension
    int NameToId(std::string _name);  // Find ID using dictionary

    int printDictionary();  // Print dictionary
};
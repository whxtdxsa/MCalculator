#pragma once
#include "dictionary.h"
class DimHandler {
private:
    Dim** arr;
    Dictionary* dict;

public:
    DimHandler(Dictionary* _dict);
    ~DimHandler();

    /* Back up the file */
    int filePull(std::string _file);
    void filePush(std::string _file);
    void bookPush(std::string _file);

    /* Basic function */
    int insertCoord(int _id, Coord _coord);
    int deleteCoord(std::string  _name, int _order);
    int clearAll();
    int printAll();
    
    /* Additional function */
    int portal();
};
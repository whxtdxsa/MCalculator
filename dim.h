#pragma once
#include <iomanip>

#include "node.h"

#define NUMOFDIM 4   // The number of dimension
#define MAXSNUM 100  // Maximum number of struct types
#define DIM0 "[OVERWORLD]"
#define DIM1 "[NETHER]"
#define DIM2 "[END]"
#define DIM3 "[BIOME]"

class Dim {
protected:
    Node** heads;          // List of heads
    std::string* s_list_;  // List of structures
    int s_num_;            // The number of structures

public:
    Dim(int _s_num, std::string* _s_list);
    virtual ~Dim();

    Node** getHeads();

    void insertNode(int _id, Coord _coord);
    int deleteNode(int _id, int _order, Coord& _deleted_coord);
    void clearList();
    int printList(void (Dim::*printFucntion)(int, int, Node*));

    virtual void printNode(int _id, int _order, Node* _node) = 0;

    virtual void printInverseNode(int _id, int _order, Node* _node){};
};

class Overworld : public Dim {
public:
    Overworld(int _s_num, std::string* _s_list) : Dim(_s_num, _s_list){};
    void printNode(int _id, int _order, Node* _node);
    void printInverseNode(int _id, int _order, Node* _node);
};

class Nether : public Dim {
public:
    Nether(int _s_num, std::string* _s_list) : Dim(_s_num, _s_list){};
    void printNode(int _id, int _order, Node* _node);
    void printInverseNode(int _id, int _order, Node* _node);
};

class End : public Dim {
public:
    End(int _s_num, std::string* _s_list) : Dim(_s_num, _s_list){};
    void printNode(int _id, int _order, Node* _node);
};

class Biome : public Dim {
public:
    Biome(int _s_num, std::string* _s_list) : Dim(_s_num, _s_list){};
    void printNode(int _id, int _order, Node* _node);

};
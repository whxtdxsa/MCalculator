#pragma once
#include <string>
#include <iostream>

struct Coord {
    int x;
    int z;

    Coord(int _x = 0, int _z = 0) : x(_x), z(_z) {}
};

std::ostream& operator<<(std::ostream& os, Coord coord);
Coord operator/(Coord coord, int num);
Coord operator*(Coord coord, int num);

class Node {
private:
    Coord coord_;
    Node* next_;

public:
    Node(Coord _coord);
    void setNext(Node* _next);
    Node* getNext();
    Coord getCoord();
};
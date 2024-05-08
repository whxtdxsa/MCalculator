#include "node.h"

std::ostream& operator<<(std::ostream& os, Coord coord) {
    os << "(" + std::to_string(coord.x) + ", " + std::to_string(coord.z) + ")";
    return os;
}

Coord operator/(Coord coord, int num) {
    coord.x /= num;
    coord.z /= num;
    return coord;
}

Coord operator*(Coord coord, int num) {
    coord.x *= num;
    coord.z *= num;
    return coord;
}

Node::Node(Coord _coord) : coord_(_coord), next_(nullptr){};

void Node::setNext(Node* _next) {
    next_ = _next;
}

Node* Node::getNext() { return next_; }

Coord Node::getCoord() { return coord_; }

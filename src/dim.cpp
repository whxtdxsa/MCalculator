#include "dim.h"

Dim::Dim(int _s_num, std::string* _s_list) : s_num_(_s_num), s_list_(_s_list) {
    /* Allocate memory */
    Coord dummy;

    heads = new Node*[s_num_];
    for (int i = 0; i < s_num_; i++) {
        /* Make dummy_node */
        Node* dummy_node = new Node(dummy);
        heads[i] = dummy_node;
    }
}

Dim::~Dim() {
    /* Release memory */
    for (int i = 0; i < s_num_; i++) {
        Node* iterator = heads[i];
        Node* prev_node = nullptr;

        while (iterator != nullptr) {
            prev_node = iterator->getNext();
            delete iterator;
            iterator = prev_node;
        }
    }
    delete[] heads;
}

Node** Dim::getHeads() { return heads; }

void Dim::insertNode(int _id, Coord _coord) {
    /*Linked List which has dummynode */
    Node* head = heads[_id];
    Node* insert_node = new Node(_coord);
    while (head->getNext() != nullptr) {
        head = head->getNext();
    }
    head->setNext(insert_node);
}

int Dim::deleteNode(int _id, int _order, Coord& _deleted_coord) {
    Node* iterator = heads[_id];
    Node* prev_node = nullptr;

    for (int order = 0; order < _order; order++) {
        prev_node = iterator;
        iterator = iterator->getNext();
        if (iterator == nullptr) return -1;  // There is no number
    }
    prev_node->setNext(iterator->getNext());
    _deleted_coord = iterator->getCoord();
    delete iterator;
    return 0;
}

void Dim::clearList() {
    /* Release memory except heads*/
    for (int i = 0; i < s_num_; i++) {
        Node* iterator = heads[i]->getNext();
        Node* prev_node = nullptr;

        while (iterator != nullptr) {
            prev_node = iterator->getNext();
            delete iterator;
            iterator = prev_node;
        }
        heads[i]->setNext(nullptr);
    }
}

int Dim::printList(void (Dim::*printFunction)(int, int, Node*)) {
    int num_of_node = 0;
    for (int id = 0; id < s_num_; id++) {
        int order = 0;  // To distinguish the same type of structure
        Node* head = heads[id];
        while (head->getNext() != nullptr) {
            // Start the node next to the dummmy
            head = head->getNext();
            (this->*printFunction)(id, ++order, head);
            num_of_node++;
        }
    }
    return num_of_node;
}

/* Different form of printing */
void Overworld::printNode(int _id, int _order, Node* _node) {
    std::cout << s_list_[_id] << " " << _order << "\t" << DIM0 << " "
              << _node->getCoord() << std::endl;
}

void Nether::printNode(int _id, int _order, Node* _node) {
    std::cout << s_list_[_id] << " " << _order << "\t" << DIM1 << " "
              << _node->getCoord() << std::endl;
}

void End::printNode(int _id, int _order, Node* _node) {
    std::cout << s_list_[_id] << " " << _order << "\t" << DIM2 << " "
              << _node->getCoord() << std::endl;
}

void Biome::printNode(int _id, int _order, Node* _node) {
    std::cout << s_list_[_id] << " " << _order << "\t" << DIM3 << " "
              << _node->getCoord() << std::endl;
}

void Overworld::printInverseNode(int _id, int _order, Node* _node) {
    std::cout << s_list_[_id] << " " << _order << "\t" << DIM0 << " ";
    std::cout << std::setw(12) << std::left << _node->getCoord();
    std::cout << "-> " << DIM1 << " " << _node->getCoord() / 8 << std::endl;
}

void Nether::printInverseNode(int _id, int _order, Node* _node) {
    std::cout << s_list_[_id] << " " << _order << "\t" << DIM1 << " ";
    std::cout << std::setw(12) << std::left << _node->getCoord();
    std::cout << "-> " << DIM0 << " " << _node->getCoord() * 8 << std::endl;
}

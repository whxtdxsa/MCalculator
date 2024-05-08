#include "dim_handler.h"

DimHandler::DimHandler(Dictionary* _dict) : dict(_dict) {
    arr = new Dim*[NUMOFDIM];
    arr[0] = new Overworld(dict->getSNum()[0], dict->getDictionary()[0]);
    arr[1] = new Nether(dict->getSNum()[1], dict->getDictionary()[1]);
    arr[2] = new End(dict->getSNum()[2], dict->getDictionary()[2]);
    arr[3] = new Biome(dict->getSNum()[3], dict->getDictionary()[3]);
}

DimHandler::~DimHandler() {
    /* Release memory */
    for (int dim = 0; dim < NUMOFDIM; dim++) {
        delete arr[dim];
    }
    delete[] arr;
}

int DimHandler::filePull(std::string _file) {
    /* Import _file. And Insert into three dimension array. */
    std::ifstream file(_file);
    if (!file.is_open()) {
        std::cout << "Failed To Open File." << std::endl;
        return -1;
    }
    std::string line;
    while (getline(file, line)) {
        std::istringstream iss(line);  // Split string and intger
        std::string buffer_name;
        Coord buffer_coord;
        if (iss >> buffer_name >> buffer_coord.x >>
            buffer_coord.z) {  // Insert into location
            int id = dict->NameToId(buffer_name);
            insertCoord(id, buffer_coord);
        }
    }
    file.close();
    return 0;
}

void DimHandler::filePush(std::string _file) {
    /* Save as file. */
    std::ofstream file(_file);
    for (int dim = 0; dim < NUMOFDIM; dim++) {
        for (int id = 0; id < dict->getSNum()[dim]; id++) {
            Node* head = arr[dim]->getHeads()[id];
            while (head->getNext() != nullptr) {
                head = head->getNext();
                std::string name = dict->getDictionary()[dim][id];
                Coord coord = head->getCoord();
                file << name << " " << coord.x << " " << coord.z << std::endl;
            }
        }
    }
    file.close();
}

void DimHandler::bookPush(std::string _file) {
    /* Save as book style. */
    std::ofstream file(_file);
    for (int dim = 0; dim < NUMOFDIM; dim++) {
        for (int id = 0; id < dict->getSNum()[dim]; id++) {
            int order = 0;
            std::string name = dict->getDictionary()[dim][id];
            Node* head = arr[dim]->getHeads()[id];
            while (head->getNext() != nullptr) {
                if (order == 0) file << name << std::endl;
                head = head->getNext();
                Coord coord = head->getCoord();
                file << ++order << ": (" << coord.x << ", " << coord.z << ")"
                     << std::endl;
            }
            if (order != 0) {
                file << std::endl;
            }
        }
    }
    file.close();
}

int DimHandler::insertCoord(int _id, Coord _coord) {
    int dim = dict->IdToDim(_id);
    if (dim == -1) {
        std::cout << "Wrong Id, Fail To Insert" << std::endl;
        return -1;
    }
    int order = dict->IdToOrder(_id);
    arr[dim]->insertNode(order, _coord);
    std::string type = dict->getDictionary()[dim][order];
    std::cout << "Inserted: " << type << " " << _coord << std::endl;
    return 0;
}

int DimHandler::deleteCoord(std::string _name, int _order) {
    int id = dict->NameToId(_name);
    if (id == -1) {
        std::cout << "Wrong Name, Fail To Delete" << std::endl;
        return -1;
    }
    int dim = dict->IdToDim(id);
    int order = dict->IdToOrder(id);
    Coord deleted_coord;
    if (arr[dim]->deleteNode(order, _order, deleted_coord) != 0) {
        std::cout << "Wrong Order, Fail To Delete" << std::endl;
        return -1;
    }
    std::cout << "Deleted: " << _name << " " << deleted_coord << std::endl;
    return 0;
}

int DimHandler::clearAll() {
    /* Delete all node */
    for (int dim = 0; dim < NUMOFDIM; dim++) arr[dim]->clearList();
    return 0;
}

int DimHandler::printAll() {
    int cnt = 0;
    for (int dim = 0; dim < NUMOFDIM; dim++) {
        cnt += arr[dim]->printList(&Dim::printNode);
    }
    if (cnt == 0) {
        std::cout << "There Is No Coordinate" << std::endl;
        return -1;
    }
    return 0;
}

int DimHandler::portal() {
    int cnt = 0;
    for (int dim = 0; dim < 2; dim++) {
        cnt += arr[dim]->printList(&Dim::printInverseNode);
    }
    if (cnt == 0) {
        std::cout << "There Is No Coordinate" << std::endl;
    }
    return 0;
}


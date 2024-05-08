#include "dictionary.h"

Dictionary::Dictionary() {
    dictionary_ = new std::string*[NUMOFDIM];      // Dimension
    for (int dim = 0; dim < NUMOFDIM; dim++) {
        dictionary_[dim] = new std::string[MAXSNUM];
    }
    s_num_ = new int[NUMOFDIM]{};  // The number of elemenet in dicionary[n]
}

Dictionary::~Dictionary() {
    /* Release memory */
    for (int dim = 0; dim < NUMOFDIM; dim++) delete[] dictionary_[dim];
    delete[] dictionary_;
    delete[] s_num_;
}

int Dictionary::dictionaryPull(std::string _file) {
    /* Import _file. And Insert into two dimension dictionary. */
    std::ifstream file(_file);
    if (!file.is_open()) {
        return -1;
    }
    std::string line;
    int dim = -1;
    int id = -1;
    while (dim <= NUMOFDIM && getline(file, line)) {
        if (line[0] == '[') {
            dim++;
            id = -1;
        } else {
            dictionary_[dim][++id] = line;
            s_num_[dim]++;
        }
    }
    file.close();
    return 0;
}

int* Dictionary::getSNum() { return s_num_; }

std::string** Dictionary::getDictionary() { return dictionary_; }

int Dictionary::NameToId(std::string _name) {
    for (int dim = 0; dim < NUMOFDIM; dim++) {
        for (int order = 0; order < s_num_[dim]; order++) {
            if (_name.compare(dictionary_[dim][order]) == 0) {
                return dim * MAXSNUM + order;
            }
        }
    }
    return -1;
}

int Dictionary::IdToOrder(int _id) { return _id % MAXSNUM; }

int Dictionary::IdToDim(int _id) { 
    int dim = _id / MAXSNUM;
    if (s_num_[dim] + MAXSNUM * dim <= _id || _id < 0) {
        return -1;
    }
    return dim;
}

int Dictionary::printDictionary() {
    for (int dim = 0; dim < NUMOFDIM; dim++) {
        /* Express dimension */
        switch (dim) {
            case 0:
                std::cout << DIM0 << std::endl;
                break;
            case 1:
                std::cout << std::endl;
                std::cout << DIM1 << std::endl;
                break;
            case 2:
                std::cout << std::endl;
                std::cout << DIM2 << std::endl;
                break;
            case 3:
                std::cout << std::endl;
                std::cout << DIM3 << std::endl;
                break;
            default:
                std::cout << std::endl;
                std::cout << "[Unknown]" << std::endl;
                break;
        }

        /* Print id and structure type */
        int column = 3;
        int cnt = 0;

        for (int order = 0; order < s_num_[dim]; order++) {
            std::cout << "(";
            std::cout.fill('0');
            std::cout << std::setw(3) << std::right << dim * MAXSNUM + order;
            std::cout << ") ";  // Express id

            std::cout.fill(' ');
            std::cout << std::setw(17) << std::left << dictionary_[dim][order] << "\t";  // Express type
            if (++cnt % column == 0) std::cout << std::endl;            // Change line
        }
        if (cnt % column != 0) std::cout << std::endl;  // Change line
    }
    return 0;
}

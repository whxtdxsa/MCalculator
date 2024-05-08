#include <windows.h>

#include "dim_handler.h"
using namespace std;

inline void setting() {
    /* Set console style */
    system("mode con:cols=75 lines=55");
    SetConsoleTitle(L"Coordinate Calculation for Minecraft");

    /* Print Logo */
    cout << "    __  ________   __________________  ___    ____________"
         << endl;
    cout << "   /  |/  /  _/ | / / ____/ ____/ __ \\/   |  / ____/_  __/"
         << endl;
    cout << "  / /|_/ // //  |/ / __/ / /   / /_/ / /| | / /_    / /   "
         << endl;
    cout << " / /  / // // /|  / /___/ /___/ _, _/ ___ |/ __/   / /    "
         << endl;
    cout << "/_/  /_/___/_/ |_/_____/\\____/_/ |_/_/  |_/_/     /_/     "
         << endl;
    cout << endl;
}

inline void printLine() { cout << string(72, '-') << endl; }

inline int controlInput(std::string id_input, int& id) {
    try {
        id = std::stoi(id_input);
        return 0;
    } catch (const std::invalid_argument& e) {
        cout << "Wrong Id, Fail To Insert" << endl;
        printLine();
        return -1;
    }
}

int main() {
    /* Set style */
    setting();

    /* Import dictionary */
    Dictionary d;
    if (d.dictionaryPull("dictionary.txt") == -1) {
        cout << "Dictionary Import Failed" << endl;
        return 0;  // If fail to find dictionary, Stop the program
    } else {
        cout << "Dictionary Import Successful" << endl;
    }

    /* Import location */
    cout
        << "Load "
           "Data---------------------------------------------------------------"
        << endl;
    DimHandler dh(&d);
    dh.filePull("location.txt");

    /* Notice commands can be used */
    printLine();
    cout << "Command: insert, delete, print, portal, clear, stop" << endl;
    printLine();

    /* Manage user's inputs */
    while (true) {
        dh.filePush("location.txt");  // Update file
        string input;
        cin >> input;

        /* If user inputs 'print' */
        if (input == "print") {
            printLine();
            dh.printAll();  // Call printfunction
            printLine();
            continue;
        }

        /* If user inputs 'insert' */
        if (input == "insert") {
            printLine();
            d.printDictionary();  // Print dictionary
            printLine();

            string input_id;
            string input_x;
            string input_z;
            Coord coord;
            cout << "Select Index Of Structure Type To Insert" << endl;
            cout << "ID: ";
            cin >> input_id;

            /* Exception handling */
            int id;
            if (controlInput(input_id, id) == -1) continue;
            if (d.IdToDim(id) == -1) {
                cout << "Wrong Id, Fail To Insert" << endl;
                printLine();
                continue;
            }

            cout << "Input Coordinate" << endl;
            cout << "X: ";
            cin >> input_x;
            if (controlInput(input_x, coord.x) == -1) continue;

            cout << "Z: ";
            cin >> input_z;
            if (controlInput(input_z, coord.z) == -1) continue;

            dh.insertCoord(id, coord);  // Call insertfunction
            printLine();
            continue;
        }

        /* If user inputs 'delete' */
        if (input == "delete") {
            printLine();
            string name;
            if (dh.printAll() == -1) {
                printLine();
                continue;
            }

            // Call printfunction
            printLine();

            cout << "Select Structure To Delete" << endl;
            cout << "Name: ";
            cin.ignore();
            getline(cin, name);

            string type;
            int index;
            istringstream iss(name);
            iss >> type >> index;

            dh.deleteCoord(type, index);  // Call deletefunction
            printLine();

            continue;
        }

        /* If user inputs 'clear' */
        if (input == "clear") {
            printLine();
            dh.clearAll();  // Call clearfunction
            cout << "All Cleaned" << endl;
            printLine();

            continue;
        }

        if (input == "portal") {
            printLine();
            dh.portal();
            printLine();

            continue;
        }

        /* If user inputs 'stop' */
        if (input == "stop") {
            break;  // End program
        }

        if (input == "format") {
            dh.bookPush("book_format.txt");
            continue;
        }
    }
    return 0;
}

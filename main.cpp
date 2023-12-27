// #include <string>
#include <iostream>

using namespace std;

int main (int argc, char ** argv) {
    int selection = 0; // 0 = random, 1 = always stay, 2 = always swap
    int numOfTrys = 0;

    string input = argv[1];

    switch (argc) {
    case 1:
        cout << "Random seleccion with random number of tries";

    case 2:
        if (input.compare("--help") == 0) {
            cout << endl << "Syntax: " << endl
                 << argv[0] << endl
                 << "\"type of selection (random for default)\"" << endl
                 << "\"number of tries (between 1 and " << INT_MAX << ", random by default)\"" << endl
                 << "\"use complete secuence (1 to do it, 0 by default)\"" << endl << endl
                 << "example: " << argv[0] << " 1 1000 1" << endl << endl;
            return EXIT_SUCCESS;
        }

        break;
    
    case 3:
        break;

    case 4:
        break;

    default:
        cout << "[ERROR] Too much arguments given." << endl;
        return EXIT_FAILURE;
    }
}
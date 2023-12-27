#include "Simulator.hpp"

using namespace std;

int main (int argc, char ** argv) {
    int selection = 0; // 0 = random, 1 = always stay, 2 = always swap
    int numOfTrys = 0;
    string input = "";

    switch (argc) {
    case 1:
        cout << "Random seleccion with random number of tries"  << endl;
        break;

    case 2:
        input = argv[1];
        if (input.compare("--help") == 0) {
            cout << endl << "Syntax: " << endl
                 << argv[0] << endl
                 << "\"type of selection (random for default)\"" << endl
                 << "\"number of tries (between 1 and " << INT_MAX << ", random by default)\"" << endl
                 << "\"use complete secuence (1 to do it, 0 by default)\"" << endl << endl
                 << "example: " << argv[0] << " 1 1000 1" << endl << endl;
            return EXIT_SUCCESS;
        }
        
        cout << 1 << " seleccion with random number of tries" << endl;

        break;
    
    case 3:
        cout << "Random seleccion with random number of tries" << endl;
        break;

    case 4:
        break;

    default:
        cout << "[ERROR] Too much arguments given." << endl;
        return EXIT_FAILURE;
    }

    cout << "algop" << endl;
    Simulator *sim = new Simulator();
    cout << "algop" << endl;
    delete sim;

    return EXIT_SUCCESS;
}
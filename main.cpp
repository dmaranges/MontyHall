#include <time.h>
#include "Simulator.hpp"

using namespace std;

int main (int argc, char ** argv) {
    srand(time(0));
    _int selection = 0; // 0 = random, 1 = always stay, 2 = always swap
    _int numOfTrys = giveRandTries(100, 10000);
    string input = "";
    Simulator *sim;

    switch (argc) {
    case 1:
        cout << "Random seleccion with random number of tries"  << endl;
        sim = new Simulator(0, numOfTrys);
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
        
        sim = new Simulator(stoi(argv[1]), numOfTrys);
        
        cout << 1 << " seleccion with random number of tries" << endl;

        break;
    
    case 3:
        cout << "X seleccion with Y number of tries" << endl;
        
        sim = new Simulator(stoi(argv[1]), stoi(argv[2]));
        break;

    default:
        cout << "[ERROR] Too much arguments given." << endl;
        return EXIT_FAILURE;
    }

    cout << "start" << endl;
    cout << "1 - successes: " << sim->simulate() << endl;
    cout << "1 total of stays: " << sim->numberOfStay() << endl;
    cout << "1 total of swaps: " << sim->numberOfSwap() << endl;
    cout << "1 total of tries: " << sim->numberOfTries() << endl;
    delete sim;

    return EXIT_SUCCESS;
}
#include <time.h>
#include "include/Simulator.hpp"

using namespace std;

int main (int argc, char ** argv) {
    srand(time(0));
    _int selection = 0; // 0 = random, 1 = always stay, 2 = always swap
    _int numOfTrys = 0;
    _int simulations = 1;
    string input = "";
    Simulator *sim;

    switch (argc) {
    case 1:
        cout << "Random seleccion with random number of tries"  << endl;
        numOfTrys = giveRandTries(100, 10000);
        sim = new Simulator(0, numOfTrys);
        break;

    case 2:
        input = argv[1];
        if (input.compare("--help") == 0) {
            cout << endl << "Syntax: " << endl
                 << argv[0] << endl
                 << "\"type of selection (random for default)\"" << endl
                 << "\"number of tries (between 1 and " << INT_MAX << ", random by default)\"" << endl
                 << "\"number of simulations (1 by default)\"" << endl << endl
                 << "example: " << argv[0] << " 1 1000 1" << endl << endl;
            return EXIT_SUCCESS;
        }

        numOfTrys = giveRandTries(100, 10000);
        sim = new Simulator(stoi(argv[1]), numOfTrys);
        
        cout << 1 << " seleccion with random number of tries" << endl;

        break;
    
    case 3:
        cout << "X seleccion with Y number of tries" << endl;
        
        sim = new Simulator(stoi(argv[1]), stoi(argv[2]));
        break;

    case 4:
        cout << "X seleccion with Y number of tries and Z number of simulations" << endl;
        
        sim = new Simulator(stoi(argv[1]), stoi(argv[2]));
        simulations = stoi(argv[3]);
        break;

    default:
        cout << "[ERROR] Too much arguments given." << endl;
        return EXIT_FAILURE;
    }

    for (_int i = 0; i < simulations; i++)
    {
        cout << "start simulation number " << i + 1 << endl;
        cout << "total of successes: " << sim->simulate() << endl;
        cout << "total of stays: " << sim->numberOfStay() << endl;
        cout << "total of swaps: " << sim->numberOfSwap() << endl;
        cout << "total of tries: " << sim->numberOfTries() << endl << endl;
    }
    
    delete sim;

    return EXIT_SUCCESS;
}
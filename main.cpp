#include <time.h>
#include "include/Simulator.hpp"

using namespace std;

void runSimulator(_int numOfSim, Simulator *sim)
{
    for (_int i = 0; i < numOfSim; i++)
    {
        cout << "start simulation number " << i + 1 << endl;
        cout << "total of successes:     " << sim->simulate() << endl;
        cout << "total of stays:         " << sim->numberOfStay() << endl;
        cout << "total of swaps:         " << sim->numberOfSwap() << endl;
        cout << "total of tries:         " << sim->numberOfTries() << endl;
        cout << "win percentage:         " << sim->winPercentage() << "%" << endl << endl;
    }

}

int main(int argc, char ** argv) {
    srand(time(0));
    _int selection = 0; // 0 = random, 1 = always stay, 2 = always swap
    _int numOfTrys = 0;
    _int typeV = 0;
    _int tryV = 0;
    _int numOfSim = 1;
    string input = "";
    Simulator *sim;

    switch (argc) {
    case 1:
        numOfTrys = giveRandRange(100, 10000);
        if (sim = new Simulator(0, numOfTrys), !sim) {
            cout << "[ERROR]: Insufficient memory for string copy." << endl;
            delete sim;
            return EXIT_FAILURE;
        }
        cout << "[DEBUG] Type of selection, tries and number of simulations by default"  << endl;
        break;

    case 2:
        input = argv[1];
        if (input.compare("--help") == 0) {
            printHelp(argv[0]);
            return EXIT_SUCCESS;
        }

        // Check first input.
        typeV = checkInput(argv[1]);
        if (typeV < 0)
            return EXIT_FAILURE;
        if (typeV > 2)
        {
            cout << "[ERROR]: Not valid type of selection" << endl;
            return EXIT_FAILURE;
        }
        numOfTrys = giveRandRange(100, 10000);

        // Create simulator obj.
        if (sim = new Simulator(typeV, numOfTrys), !sim) {
            cout << "[ERROR]: Insufficient memory for string copy." << endl;
            delete sim;
            return EXIT_FAILURE;
        }
        
        cout << "[DEBUG] Type of selection equal to " << typeV
             << ", tries and number of simulations by default"  << endl;

        break;
    
    case 3:        
        // Check first input.
        typeV = checkInput(argv[1]);
        if (typeV < 0)
            return EXIT_FAILURE;
        if (typeV > 2)
        {
            cout << "[ERROR]: Not valid type of selection" << endl;
            return EXIT_FAILURE;
        }
        // Check second input.
        tryV = checkInput(argv[2]);
        if (tryV < 0)
            return EXIT_FAILURE;
        
        // Create simulator obj.
        if (sim = new Simulator(typeV, tryV), !sim) {
            cout << "[ERROR]: Insufficient memory for string copy." << endl;
            delete sim;
            return EXIT_FAILURE;
        }

        cout << "[DEBUG] Type of selection equal to " << typeV
             << ", tries equal to " << tryV
             << "and number of simulations by default"  << endl;
        break;

    case 4:        
        // Check first input.
        typeV = checkInput(argv[1]);
        if (typeV < 0)
        {
            return EXIT_FAILURE;
        }
        if (typeV > 2)
        {
            cout << "[ERROR]: Not valid type of selection" << endl;
            return EXIT_FAILURE;
        }
        // Check second input.
        tryV = checkInput(argv[2]);
        if (tryV < 0)
            return EXIT_FAILURE;
        // Check third input.
        numOfSim = checkInput(argv[3]);
        if (numOfSim < 0)
            return EXIT_FAILURE;
        
        // Create simulator obj.
        if (sim = new Simulator(typeV, tryV), !sim) {
            cout << "[ERROR]: Insufficient memory for string copy." << endl;
            delete sim;
            return EXIT_FAILURE;
        }
        cout << "[DEBUG] Type of selection equal to " << typeV
             << ", tries equal to " << tryV
             << "and " << numOfSim << " number of simulations"<< endl;
        break;

    default:
        cout << "[ERROR] Too much arguments given." << endl;
        return EXIT_FAILURE;
    }
    
    runSimulator(numOfSim, sim);
    delete sim;

    return EXIT_SUCCESS;
}
#include <time.h>
#include "include/Simulator.hpp"

using namespace std;

_int checkInput(string str)
{
    cout << str << endl;
    _int inpValue = -1;
    try
    {
        inpValue = stoi(str);
        if (inpValue < 0)
            cout << "[ERROR] wrong input: " << str << endl;
    }
    catch(const std::exception& e)
    {
        cout << "[ERROR] wrong input: " << str << endl;
    }
    return inpValue;
}

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

void printHelp(string arg)
{
    cout << endl << "Syntax: " << endl
         << arg << endl
         << "\"type of selection (random for default)\"" << endl
         << "\"number of tries (between 1 and " << INT_MAX << ", random by default)\"" << endl
         << "\"number of simulations (1 by default)\"" << endl << endl
         << "example: " << arg << " 1 1000 1" << endl << endl;
}

int main (int argc, char ** argv) {
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
        numOfTrys = giveRandTries(100, 10000);
        if (sim = new Simulator(0, numOfTrys), !sim) {
            cout << "[ERROR]: Insufficient memory for string copy." << endl;
            delete sim;
            return EXIT_FAILURE;
        }
        cout << "Type of selection, tries and number of simulations by default"  << endl;
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
        numOfTrys = giveRandTries(100, 10000);

        // Create simulator obj.
        if (sim = new Simulator(typeV, numOfTrys), !sim) {
            cout << "[ERROR]: Insufficient memory for string copy." << endl;
            delete sim;
            return EXIT_FAILURE;
        }
        
        cout << "Type of selection equal to " << typeV
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

        cout << "Type of selection equal to " << typeV
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
        cout << "Type of selection equal to " << typeV
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
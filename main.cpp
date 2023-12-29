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
    _int typeV = 0;
    _int tryV = 0;
    _int numOfSim = 1;
    string input = "";
    Simulator *sim;

    // Return error because the inputs arguments are more than 3
    if (argc > 4)
    {
        log("[ERROR] Too much arguments given.");
        return EXIT_FAILURE;
    }

    // Print help description
    if (argc == 2 && input.compare("--help") == 0)
    {
        printHelp(argv[0]);
        return EXIT_SUCCESS;
    }

    // Set base case
    if (argc == 1)
    {
        typeV = 0;
        tryV = giveRandRange(100, 10000);
        log("[DEBUG] Type of selection, tries and number of simulations by default");
    }
    
    // Set "typeV" and "tryV" variables, depending on the number of inputs
    for (size_t it = 1; it < argc; it++)
    {
        if (it == 1)
        {
            typeV = checkInput(argv[it]);
            if (typeV < 0)
                return EXIT_FAILURE;

            if (typeV > 2)
            {
                log("[ERROR]: Not valid type of selection");
                return EXIT_FAILURE;
            }

            if (argc == 2)
            {
                tryV = giveRandRange(100, 10000);

                log("[DEBUG] Type of selection equal to " << typeV
                    << ", tries and number of simulations by default");
            }
        }
        else if (it == 2)
        {
            tryV = checkInput(argv[it]);
            if (tryV < 0)
                return EXIT_FAILURE;
            if (argc == 3)
            {
                log("[DEBUG] Type of selection equal to " << typeV
                    << ", tries equal to " << tryV
                    << "and number of simulations by default");
            }
        }
        else
        {
            numOfSim = checkInput(argv[3]);
            if (numOfSim < 0)
                return EXIT_FAILURE;
                log("[DEBUG] Type of selection equal to " << typeV
                    << ", tries equal to " << tryV
                    << "and " << numOfSim << " number of simulations");
        }
        
    }
    
    // Create simulator obj.
    if (sim = new Simulator(typeV, tryV), !sim) {
        log("[ERROR]: Insufficient memory for string copy.");
        delete sim;
        return EXIT_FAILURE;
    }
    
    runSimulator(numOfSim, sim);
    delete sim;

    return EXIT_SUCCESS;
}

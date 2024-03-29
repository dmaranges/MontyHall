#include "../include/Simulator.hpp"

using namespace std;

Simulator::Simulator(_int type, _int tries) :
    typeOfSlct(type),
    numOfTries(tries),
    stay(0),
    swap(0),
    totalWin(0)
{

}

Simulator::~Simulator()
{
}

_int Simulator::simulate()
{
    // Reset previus simulation.
    swap = 0;
    stay = 0;
    totalWin = 0;

    for (_int i = 0; i < numOfTries; i++)
    {
        _int winDoor = giveRandOneToThre();
        _int slctDoor = giveRandOneToThre();
        _int selection = typeOfSlct;

        if (typeOfSlct == 0) // Select random type in case 0
        {
            (oneOrTwo() == 1) ? selection = 1 : selection = 2;
        }
        
        if (selection == 1)
        {
            ++stay;
            tryToHit(winDoor, slctDoor, totalWin, &isEq);
        }
        else
        {
            ++swap;
            tryToHit(winDoor, slctDoor, totalWin, &notEq);
        }
    }
    
    return totalWin;
}

_int Simulator::numberOfStay()
{
    return stay;
}

_int Simulator::numberOfSwap()
{
    return swap;
}

_int Simulator::numberOfTries()
{
    return numOfTries;
}

_int Simulator::winPercentage()
{
    return (numOfTries != 0) ? ((totalWin * 100) / numOfTries) : 0;
}

void Simulator::printResults(_int numOfSim)
{
    cout << "start simulation number " << numOfSim << endl;
    cout << "total of successes:     " << totalWin << endl;
    cout << "total of stays:         " << stay << endl;
    cout << "total of swaps:         " << swap << endl;
    cout << "total of tries:         " << numOfTries << endl;
    cout << "win percentage:         " << winPercentage() << "%" << endl << endl;
}

void Simulator::tryToHit(_int winDoor, _int slctDoor, _int &totalWin, bool(*func)(int, int))
{
    func(winDoor, slctDoor) ? totalWin++ : 0;
}

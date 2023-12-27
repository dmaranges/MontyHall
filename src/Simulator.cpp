#include "../include/Simulator.hpp"

using namespace std;

Simulator::Simulator(_int type, _int tries) : typeOfSlct(type), numOfTries(tries)
{

}

Simulator::~Simulator()
{
}

_int Simulator::simulate()
{
    swap = 0;
    stay = 0;
    _int totalWin = 0;
    for (_int i = 0; i < numOfTries; i++)
    {
        _int winDoor = giveRandSelection();
        _int slctDoor = giveRandSelection();
        if (typeOfSlct == 0)
        {
            _int stayOrSwap = oneOrTwo();
            if (stayOrSwap == 1)
            {
                ++stay;
                tryToHit(winDoor, slctDoor, totalWin, &isEq);
            }
            else if (stayOrSwap == 2)
            {
                ++swap;
                tryToHit(winDoor, slctDoor, totalWin, &notEq);
            }
        }
        else if (typeOfSlct == 1)
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

void Simulator::tryToHit(_int winDoor, _int slctDoor, _int &totalWin, bool(*func)(int, int))
{
    func(winDoor, slctDoor) ? totalWin++ : 0;
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

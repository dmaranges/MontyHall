#include "Simulator.hpp"

using namespace std;

Simulator::Simulator(_int type, _int tries) : typeOfSlct(type), numOfTries(tries)
{

}

Simulator::~Simulator()
{
}

_int Simulator::simulate()
{
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
                if (winDoor == slctDoor)
                {
                    ++totalWin;
                }
            }
            else if (stayOrSwap == 2)
            {
                ++swap;
                if (winDoor != slctDoor)
                {
                    ++totalWin;
                }
            }
        }
        else if (typeOfSlct == 1)
        {
            ++stay;
            if (winDoor == slctDoor)
            {
                ++totalWin;
            }
        }
        else
        {
            ++swap;
            if (winDoor != slctDoor)
            {
                ++totalWin;
            }
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

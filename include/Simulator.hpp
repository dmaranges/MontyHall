#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include <string>
#include <iostream>
#include <functional>

#include "Utils.hpp"

class Simulator
{
    public:
        Simulator(_int type, _int tries);
        ~Simulator();
        _int simulate();
        _int numberOfStay();
        _int numberOfSwap();
        _int numberOfTries();
        
    protected:
        void tryToHit(_int winDoor, _int slctDoor, _int &totalWin, bool(*func)(int, int));

    private:
        _int numberOfSimulations; // Total of simulations when call 

        _int typeOfSlct;
        _int numOfTries;

        _int stay;
        _int swap;
};

#endif

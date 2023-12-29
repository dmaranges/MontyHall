#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include <string>
#include <iostream>
#include <functional>

#include "Utils.hpp"

class Simulator
{
    public:
        /*********************************************************************************
         * Set how the competitor will decide if change or not the first selection and
         * how many tries or game will be done.
        *********************************************************************************/
        Simulator(_int type, _int tries);

        /*********************************************************************************
         * Simulator destructor. In this case, do nothing.
        *********************************************************************************/
        ~Simulator();
        
        /*********************************************************************************
         * It resets the previous simulation and start new. This simulation returns how
         * many times the competitor wins.
        *********************************************************************************/
        _int simulate();
        
        /*********************************************************************************
         * Return how many times stay the option in the last simulation.
        *********************************************************************************/
        _int numberOfStay();
        
        /*********************************************************************************
         * Return how many times swap the option in the last simulation.
        *********************************************************************************/
        _int numberOfSwap();

        /*********************************************************************************
         * Return how many attempts are specified.
        *********************************************************************************/
        _int numberOfTries();

        /*********************************************************************************
         * Return the percentage (between 0 and 100) of win rate in the last simulation.
        *********************************************************************************/
        _int winPercentage();
        
    protected:
        /*********************************************************************************
         * Evaluate if the selected door is the winner taking in mind if swap or not.
        *********************************************************************************/
        void tryToHit(_int winDoor, _int slctDoor, _int &totalWin, bool(*func)(int, int));

    private:
        _int typeOfSlct; // Type of selection (swap or stay) "0 = random", "1 = stay", "2 = swap"
        _int numOfTries; // Quantity of tries to simulate
        _int totalWin; // Quantity of wins

        _int stay; // Save the number of situations where swaps the selection.
        _int swap; // Save the number of situations where stays the selection.
};

#endif

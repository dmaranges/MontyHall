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
         * Set how the competitor will deside if change or not the first selection and
         * how meny tries or game will be do.
        *********************************************************************************/
        Simulator(_int type, _int tries);

        ~Simulator();
        
        /*********************************************************************************
         * Reset previus simulation and start new. That simulation return how many times
         * the competitor win.
        *********************************************************************************/
        _int simulate();
        
        /*********************************************************************************
         * Return how many times stay the option are taking in the simulation.
        *********************************************************************************/
        _int numberOfStay();
        
        /*********************************************************************************
         * Return how many times swap the option are taking in the simulation.
        *********************************************************************************/
        _int numberOfSwap();

        /*********************************************************************************
         * Return how many tries are specify.
        *********************************************************************************/
        _int numberOfTries();

        /*********************************************************************************
         * Return the percentage (between 0 to 100) of win in the last simulation.
        *********************************************************************************/
        _int winPercentage();
        
    protected:
        /*********************************************************************************
         * Evaluate if the selected door is the winner teking in mind if swap or not.
         * That part is take it from the function pass it like parameter.
        *********************************************************************************/
        void tryToHit(_int winDoor, _int slctDoor, _int &totalWin, bool(*func)(int, int));

    private:
        _int typeOfSlct; // Type of selection (swap or stay) "0 = rand", "1 = stay", "2 = swap"
        _int numOfTries; // Quantity of tries to simulate
        _int totalWin; // Quantity of wins

        _int stay; // Save the number of situations where the competitor do not chage the seleccion in the simulation
        _int swap; // Save the number of situations where the competitor chage the seleccion in the simulation
};

#endif

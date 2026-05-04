#include "Simulator.hpp"
#include "WinningDoor.hpp"
#include "LosingDoor.hpp"

#include <string>
#include <iostream>
#include <functional>

using namespace std;

Simulator::Simulator(unsigned int numberOfDoors) :
    nod(numberOfDoors)
{
    const unsigned int winningDoorPosition = getRandomChose(0, numberOfDoors);
    for (unsigned int door = 0; door < numberOfDoors; door++)
    {
        if (door == winningDoorPosition)
        {
            doors.push_back(make_unique<WinningDoor>());
        }
        else
        {
            doors.push_back(make_unique<LosingDoor>());
        }
    }
}

Simulator::~Simulator()
{
}

void Simulator::startSimulation(Simulation& simulation) {
    const Desition dSelected = simulation.desition;
    bool keep = true;

    for (int i = 0; i < simulation.numOfTries; i++)
    {
        if (dSelected == Desition::AlwaysChange) {
            if (!doors[getRandomChose(0, nod)]->winningDoor())
                simulation.totalWin++;
        } else if (dSelected == Desition::AlwaysKeep) {
            if (doors[getRandomChose(0, nod)]->winningDoor())
                simulation.totalWin++;
        } else {
            keep = getRandomBool();
            if (doors[getRandomChose(0, nod)]->winningDoor() && keep
                || !doors[getRandomChose(0, nod)]->winningDoor() && !keep)
            {
                simulation.totalWin++;
            }
            keep ? simulation.stay++ : simulation.swap++;
        }
    }
    
}

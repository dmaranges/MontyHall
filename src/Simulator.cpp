#include "Simulator.hpp"
#include "Utils.hpp"
#include "WinningDoor.hpp"
#include "LosingDoor.hpp"

#include <string>
#include <iostream>
#include <functional>
#include <memory>

using namespace std;

Simulator::Simulator(unsigned int numberOfDoors) :
    nod(numberOfDoors)
{
    const unsigned int winningDoorPosition = (rand() % numberOfDoors);
    std::vector<std::unique_ptr<Door>> createDoors(numberOfDoors);
    for (unsigned int doors = 0; doors < numberOfDoors; doors++)
    {
        if (doors == numberOfDoors)
        {
            createDoors.push_back(make_unique<WinningDoor>());
        }
        else
        {
            createDoors.push_back(make_unique<LosingDoor>());
        }
    }
    doors = createDoors;
}

Simulator::~Simulator()
{
}

void Simulator::startSimulation(Simulation& simulation) {

}

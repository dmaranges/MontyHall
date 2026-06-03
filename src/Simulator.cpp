#include "Simulator.hpp"

#include <functional>
#include <iostream>
#include <string>

#include "LosingDoor.hpp"
#include "WinningDoor.hpp"

using namespace std;

Simulator::Simulator(unsigned int numberOfDoors,
                     unsigned int numberOfWiningDoors)
    : nod(numberOfDoors), nowd(numberOfWiningDoors) {
  const unsigned int winningDoorPosition =
      Utils::getRandomChose(0, numberOfDoors);
  for (unsigned int door = 0; door < numberOfDoors; door++) {
    if (door == winningDoorPosition) {
      doors.push_back(make_unique<WinningDoor>());
    } else {
      doors.push_back(make_unique<LosingDoor>());
    }
  }
}

Simulator::~Simulator() {}

void Simulator::startSimulation(Utils::Simulation& simulation) {
  const Utils::Desition dSelected = simulation.desition;
  bool keep = true;

  for (int i = 0; i < simulation.numOfTries; i++) {
    if (dSelected == Utils::Desition::AlwaysChange) {
      if (!doors[Utils::getRandomChose(0, nod)]->winningDoor())
        simulation.totalWin++;
    } else if (dSelected == Utils::Desition::AlwaysKeep) {
      if (doors[Utils::getRandomChose(0, nod)]->winningDoor())
        simulation.totalWin++;
    } else {
      keep = Utils::getRandomBool();
      if (doors[Utils::getRandomChose(0, nod)]->winningDoor() && keep ||
          !doors[Utils::getRandomChose(0, nod)]->winningDoor() && !keep) {
        simulation.totalWin++;
      }
      keep ? simulation.stay++ : simulation.swap++;
    }
  }
}

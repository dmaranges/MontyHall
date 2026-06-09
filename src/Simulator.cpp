#include "Simulator.hpp"

#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <thread>

#include "LosingDoor.hpp"
#include "WinningDoor.hpp"

using namespace std;

static int actualTry = 0;

thread_local int localSimulationWins;

Simulator::Simulator(Utils::Simulation&& simulation)
    : sim(std::move(simulation)) {
  auto winningDoorPositions = Utils::getRandomChoses(
      0, simulation.numberOfDoors, simulation.numberOfWiningDoors);

  for (int door = 0; door < simulation.numberOfDoors; door++) {
    if (isWinner(door, winningDoorPositions))
      doors.push_back(make_unique<WinningDoor>());
    else
      doors.push_back(make_unique<LosingDoor>());
  }
  if (sim.typeOfSimulation == 0)
    simulation.desition = static_cast<Utils::Desition>(simulation.strategyType);
}

Simulator::~Simulator() {}

void Simulator::startSimulation() {
  const bool clasicMontyHallSelected = sim.desition.has_value();
  startThreadPoolSimulations(clasicMontyHallSelected);
}

bool Simulator::isWinner(int door, std::vector<int>& wDoors) {
  return find(wDoors.begin(), wDoors.end(), door) != wDoors.end();
}

void Simulator::startThreadPoolSimulations(const bool simulationType) {
  std::vector<std::thread> tasks;
  if (simulationType) {
    for (size_t i = 0; i < 4; i++) {
      tasks.emplace_back(&Simulator::clasicMontyHallSimulation, this);
    }

  } else {
    for (size_t i = 0; i < 4; i++) {
      tasks.emplace_back(&Simulator::customMontyHallSimulation, this);
    }
  }
  for (std::thread& t : tasks)
    if (t.joinable()) t.join();

  Utils::printResults(sim);
}

void Simulator::clasicMontyHallSimulation() {
  bool keep = true;

  while (true) {
    if (sim.desition == Utils::Desition::AlwaysChange) {
      if (!doors[Utils::getRandomChose(0, nod)]->winningDoor())
        localSimulationWins++;
    } else if (sim.desition == Utils::Desition::AlwaysKeep) {
      if (doors[Utils::getRandomChose(0, nod)]->winningDoor())
        localSimulationWins++;
    } else {
      keep = Utils::getRandomBool();
      if (doors[Utils::getRandomChose(0, nod)]->winningDoor() && keep ||
          !doors[Utils::getRandomChose(0, nod)]->winningDoor() && !keep) {
        localSimulationWins++;
      }
      {
        mtx.lock();
        keep ? sim.stay++ : sim.swap++;
        mtx.unlock();
      }
      sim.totalWin += localSimulationWins;
    }
  }
  sim.totalWin += localSimulationWins;
}

void Simulator::customMontyHallSimulation() {
  {
    // C++11 block mtx until out of scoup but not avoid Deadlock
    std::lock_guard<std::mutex> lock(mtx);
    sim.numberOfSwaps == 0 ? sim.numberOfSwaps = 1 : 0;
  }
  auto desition =
      Utils::getRandomChoses(0, sim.numberOfDoors, sim.numberOfSwaps);

  while (true) {
    if (doors[desition.back()]->winningDoor()) localSimulationWins++;
    {
      // C++17 block mtx until out of scoup but not avoid Deadlock
      std::scoped_lock lock(mtx);
      if (++actualTry >= sim.numOfTries) {
        cout << "thread total win = " << localSimulationWins << endl;
        break;
      }
    }
    desition = Utils::getRandomChoses(0, sim.numberOfDoors, sim.numberOfSwaps);
  }

  sim.totalWin += localSimulationWins;
}

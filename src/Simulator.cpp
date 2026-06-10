#include "Simulator.hpp"

#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <thread>

#include "LosingDoor.hpp"
#include "WinningDoor.hpp"
#include "log.hpp"

using namespace std;

static int actualTry = 0;

thread_local int localSimulationWins;

Simulator::Simulator(Utils::Simulation&& simulation)
    : sim(std::move(simulation)) {
  auto winningDoorPositions = Utils::getRandomChoses(
      0, simulation.numberOfDoors, simulation.numberOfWinningDoors);

  for (int door = 0; door < simulation.numberOfDoors; door++) {
    if (isWinner(door, winningDoorPositions))
      doors.push_back(make_unique<WinningDoor>());
    else
      doors.push_back(make_unique<LosingDoor>());
  }
  // store sizes locally
  numberOfDoors = simulation.numberOfDoors;
  numberOfWinningDoors = simulation.numberOfWinningDoors;
  if (sim.typeOfSimulation == 0)
    simulation.decision = static_cast<Utils::Decision>(simulation.strategyType);
}

Simulator::~Simulator() {}

void Simulator::startSimulation() {
  const bool clasicMontyHallSelected = sim.decision.has_value();
  startThreadPoolSimulations(clasicMontyHallSelected);
}

bool Simulator::isWinner(int door, std::vector<int>& wDoors) {
  return find(wDoors.begin(), wDoors.end(), door) != wDoors.end();
}

void Simulator::startThreadPoolSimulations(const bool simulationType) {
  std::vector<std::thread> tasks;
  if (simulationType) {
    LOG_INFO("Generating classic monty hall simulation with ",
             sim.numberOfTries, " tries...");
    for (size_t i = 0; i < 4; i++) {
      tasks.emplace_back(&Simulator::clasicMontyHallSimulation, this);
    }

  } else {
    LOG_INFO("Generating custom monty hall simulation with ", sim.numberOfSwaps,
             " swaps and ", sim.numberOfTries, " tries...");
    for (size_t i = 0; i < 4; i++) {
      tasks.emplace_back(&Simulator::customMontyHallSimulation, this);
    }
  }
  for (std::thread& t : tasks)
    if (t.joinable()) t.join();

  LOG_INFO("join all threads");
  Utils::printResults(sim);
}

void Simulator::clasicMontyHallSimulation() {
  bool keep = true;

  mtx.lock();
  if (++actualTry >= sim.numberOfTries) return;
  mtx.unlock();

  LOG_DEBUG("start thread id = ", this_thread::get_id());
  while (true) {
    LOG_DEBUG("thread id = ", this_thread::get_id(),
              ", actual try = ", actualTry);
    if (sim.decision == Utils::Decision::AlwaysChange) {
      if (!doors[Utils::getRandomChose(0, numberOfDoors)]->winningDoor())
        localSimulationWins++;
    } else if (sim.decision == Utils::Decision::AlwaysKeep) {
      if (doors[Utils::getRandomChose(0, numberOfDoors)]->winningDoor())
        localSimulationWins++;
    } else {
      keep = Utils::getRandomBool();
      if (doors[Utils::getRandomChose(0, numberOfDoors)]->winningDoor() &&
              keep ||
          !doors[Utils::getRandomChose(0, numberOfDoors)]->winningDoor() &&
              !keep) {
        localSimulationWins++;
      }
      mtx.lock();
      keep ? sim.stays++ : sim.swaps++;
      mtx.unlock();
    }
    std::scoped_lock lock(mtx);
    if (++actualTry >= sim.numberOfTries) {
      LOG_INFO("thread total win = ", localSimulationWins);
      break;
    }
  }
  sim.totalWins += localSimulationWins;
  LOG_INFO("Simulation completed. Total wins: ", sim.totalWins.load());
}

void Simulator::customMontyHallSimulation() {
  {
    LOG_DEBUG("C++11 block mtx until out of scope but does not avoid Deadlock");
    std::lock_guard<std::mutex> lock(mtx);
    if (++actualTry >= sim.numberOfTries) return;
    sim.numberOfSwaps == 0 ? sim.numberOfSwaps = 1 : 0;
    LOG_DEBUG("start thread id = ", this_thread::get_id());
  }
  auto decisionIndices =
      Utils::getRandomChoses(0, sim.numberOfDoors, sim.numberOfSwaps);

  while (true) {
    LOG_DEBUG("thread id = ", this_thread::get_id(),
              ", actual try = ", actualTry);
    if (doors[decisionIndices.back()]->winningDoor()) localSimulationWins++;
    {
      LOG_DEBUG(
          "C++17 block mtx until out of scope but does not avoid Deadlock");
      std::scoped_lock lock(mtx);
      if (++actualTry >= sim.numberOfTries) {
        LOG_INFO("thread total win = ", localSimulationWins);
        break;
      }
    }
    decisionIndices =
        Utils::getRandomChoses(0, sim.numberOfDoors, sim.numberOfSwaps);
  }

  sim.totalWins += localSimulationWins;
  LOG_INFO("Simulation completed. Local wins: ", localSimulationWins,
           ", Total wins: ", sim.totalWins.load());
}

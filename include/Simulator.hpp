#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include <atomic>
#include <memory>
#include <mutex>
#include <vector>

#include "Door.hpp"
#include "Utils.hpp"

class Simulator {
 public:
  Simulator(Utils::Simulation&& simulation);

  ~Simulator();

  void startSimulation();

  int totalWins() const;
  int totalStays() const;
  int totalSwaps() const;
  int totalTries() const;

 private:
  bool isWinner(int door, std::vector<int>& doors);
  void startThreadPoolSimulations(const bool simulationType);
  void clasicMontyHallSimulation();
  void customMontyHallSimulation();

  unsigned int numberOfDoors;         // numberOfDoors
  unsigned int numberOfWinningDoors;  // numberOfWinningDoors
  Utils::Simulation sim;
  std::mutex mtx;
  std::vector<std::unique_ptr<Door>> doors;

  friend void Utils::printResults(Simulation& sim);
};

#endif

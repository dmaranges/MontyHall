#ifndef UTILS_HPP
#define UTILS_HPP

#include <stdlib.h>

#include <iostream>
#include <optional>
#include <random>

#include "LosingDoor.hpp"
#include "WinningDoor.hpp"
#include "log.hpp"

#define log(s) (std::cout << s << endl)

using namespace std;

namespace Utils {

enum Decision { Aleatory, AlwaysKeep, AlwaysChange };

struct Simulation {
  // Type of selection (swap or stay) "0 = random", "1 = stay", "2 = swap"
  optional<Decision> decision;

  int strategyType = 0;
  int numberOfDoors = 3;
  int numberOfWinningDoors = 1;
  int numberOfSwaps = 0;

  int numberOfTries = 1000;        // Quantity of tries to simulate
  std::atomic<int> totalWins = 0;  // Quantity of wins

  int stays = 0;  // Count of times user stayed
  int swaps = 0;  // Count of times user swapped

  int typeOfSimulation = 0;
  // Default normal constructor
  Simulation() = default;

  // MOVE CONSTRUCTOR
  Simulation(Simulation&& other) noexcept {
    this->decision = other.decision;
    this->numberOfDoors = other.numberOfDoors;
    this->numberOfWinningDoors = other.numberOfWinningDoors;
    this->numberOfTries = other.numberOfTries;
    this->strategyType = other.strategyType;
    this->typeOfSimulation = other.typeOfSimulation;
    this->totalWins.store(other.totalWins.load());
  }
  /*
    Simulation& operator=(Simulation&& other) noexcept {
      this->decision = other.decision;
      this->numberOfDoors = other.numberOfDoors;
      this->numberOfWinningDoors = other.numberOfWinningDoors;
      this->numberOfTries = other.numberOfTries;
      this->strategyType = other.strategyType;
      this->typeOfSimulation = other.typeOfSimulation;
      this->totalWins.store(other.totalWins.load());
      return *this;
    }*/
};

inline int getRandomBool() {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  static std::bernoulli_distribution d(0.5);  // 0.5 probability for true
  return d(gen);
}

inline int getRandomChose(int minValue, int maxValue) {
  // 1. Obtain a random seed from hardware
  std::random_device rd;
  // 2. Initialize the generator engine (Mersenne Twister) with the seed
  std::mt19937 gen(rd());
  // 3. Define the range [min, max] (e.g., 1 to 100 inclusive)
  std::uniform_int_distribution<> distrib(minValue, maxValue - 1);

  // 4. Generate the number
  return distrib(gen);
}

inline vector<int> getRandomChoses(int minValue, int maxValue, int length) {
  std::vector<int> numbers;
  numbers.reserve(length);  // Optimize memory by reserving space in advance

  // 1. Initialize the randomness device (seed)
  std::random_device rd;

  // 2. Initialize the generator engine with the seed
  std::mt19937 gen(rd());

  // 3. Define the uniform distribution between a and b
  // maxValue is exclusive upper bound for choosing indices [minValue,
  // maxValue-1]
  std::uniform_int_distribution<int> distribucion(minValue, maxValue - 1);

  // 4. Fill the vector
  for (int i = 0; i < length; ++i) {
    numbers.push_back(distribucion(gen));
  }

  return numbers;
}

inline std::vector<std::unique_ptr<Door>> getRandomWinningDoors(
    int numOfDoors, int numOfWinningDoors) {
  std::vector<std::unique_ptr<Door>> doors(numOfDoors);
  if (numOfDoors <= 0 || numOfDoors <= numOfWinningDoors) return doors;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::vector<double> weights(numOfDoors, 1);
  std::discrete_distribution<> d(weights.begin(), weights.end());
  bool winner = numOfWinningDoors < numOfDoors - numOfWinningDoors;

  if (winner) {
    int selected = 0;
    for (int i = 0; i < numOfWinningDoors; i++) {
      selected = d(gen);
      weights[selected] = 0;
    }
  } else {
    int selected = 0;
    for (int i = 0; i < numOfDoors - numOfWinningDoors; i++) {
      selected = d(gen);
      weights[selected] = 0;
    }
  }

  for (auto door : weights) {
    if (winner && door == 0 || !winner && door == 1) {
      doors.push_back(make_unique<WinningDoor>());
    } else {
      doors.push_back(make_unique<LosingDoor>());
    }
  }

  return doors;
}

inline void printResults(Simulation& sim) {
  LOG_INFO("Number of doors: ", sim.numberOfDoors);
  LOG_INFO("Number of tries: ", sim.numberOfTries);
  LOG_INFO("Number of winning doors: ", sim.numberOfWinningDoors);
  LOG_INFO("Number of swaps (custom): ", sim.numberOfSwaps);
  LOG_INFO("Strategy type: ", sim.strategyType);

  LOG_INFO("Total tries: ", sim.numberOfTries);
  LOG_INFO("Total swaps: ", sim.swaps);
  LOG_INFO("Total stays: ", sim.stays);
  LOG_INFO("Total wins: ", sim.totalWins.load());
}

}  // namespace Utils

#endif
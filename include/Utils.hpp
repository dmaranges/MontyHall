#ifndef UTILS_HPP
#define UTILS_HPP

#include <stdlib.h>

#include <iostream>
#include <random>

#include "LosingDoor.hpp"
#include "WinningDoor.hpp"

#define log(s) (std::cout << s << endl)

using namespace std;

namespace Utils {

enum Desition { Aleatory, AlwaysKeep, AlwaysChange };

struct Simulation {
  Desition desition;  // Type of selection (swap or stay) "0 = random", "1 =
                      // stay", "2 = swap"
  int numOfTries;     // Quantity of tries to simulate
  int totalWin;       // Quantity of wins

  int stay;  // Save the number of situations where swaps the selection.
  int swap;  // Save the number of situations where stays the selection.
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

}  // namespace Utils

#endif
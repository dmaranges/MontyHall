#ifndef UTILS_HPP
#define UTILS_HPP

#include <stdlib.h>

#include <iostream>
#include <optional>
#include <random>

#include "LosingDoor.hpp"
#include "WinningDoor.hpp"

#define log(s) (std::cout << s << endl)

using namespace std;

namespace Utils {

enum Desition { Aleatory, AlwaysKeep, AlwaysChange };

struct Simulation {
  // Type of selection (swap or stay) "0 = random", "1 = stay", "2 = swap"
  optional<Desition> desition;

  int strategyType = 0;
  int numberOfDoors = 3;
  int numberOfWiningDoors = 1;
  int numberOfSwaps = 0;

  int numOfTries = 1000;          // Quantity of tries to simulate
  std::atomic<int> totalWin = 0;  // Quantity of wins

  int stay = 0;  // Save the number of situations where swaps the selection.
  int swap = 0;  // Save the number of situations where stays the selection.

  int typeOfSimulation = 0;
  // Constructor por defecto normal
  Simulation() = default;

  // CONSTRUCTOR DE MOVIMIENTO
  Simulation(Simulation&& other) noexcept {
    this->desition = other.desition;
    this->numberOfDoors = other.numberOfDoors;
    this->numberOfWiningDoors = other.numberOfWiningDoors;
    this->numOfTries = other.numOfTries;
    this->strategyType = other.strategyType;
    this->typeOfSimulation = other.typeOfSimulation;
    this->totalWin.store(other.totalWin.load());
  }
  /*
    Simulation& operator=(Simulation&& other) noexcept {
      this->desition = other.desition;
      this->numberOfDoors = other.numberOfDoors;
      this->numberOfWiningDoors = other.numberOfWiningDoors;
      this->numOfTries = other.numOfTries;
      this->strategyType = other.strategyType;
      this->typeOfSimulation = other.typeOfSimulation;
      this->totalWin.store(other.totalWin.load());
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
  numbers.reserve(
      length);  // Optimizamos memoria reservando el espacio de antemano

  // 1. Inicializar el dispositivo de aleatoriedad (semilla)
  std::random_device rd;

  // 2. Inicializar el motor generador con la semilla
  std::mt19937 gen(rd());

  // 3. Definir la distribución uniforme entre a y b
  std::uniform_int_distribution<int> distribucion(minValue, maxValue);

  // 4. Llenar el vector
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
  cout << "numero de puertas" << sim.numberOfDoors << endl
       << "numero de intentos" << sim.numOfTries << endl
       << "numero de puertas de victorias" << sim.numberOfWiningDoors << endl
       << "numero de cambios en custom" << sim.numberOfSwaps << endl
       << "tipo de estrategia" << sim.strategyType << endl
       << endl;

  cout << "Total de intentos : " << sim.numOfTries << endl
       << "Total de swap : " << sim.swap << endl
       << "total de stay : " << sim.stay << endl
       << "Total de victorias : " << sim.totalWin << endl
       << endl;
}

}  // namespace Utils

#endif
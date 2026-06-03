#include <time.h>

#include <functional>
#include <iostream>
#include <string>

#include "ConsoleInputs.hpp"
#include "Simulator.hpp"
#include "Utils.hpp"

using namespace std;

int main(int argc, char** argv) {
  Utils::Simulation simulation{Utils::Desition::Aleatory};
  Simulator* simulator = new Simulator(3, 1);

  simulator->startSimulation(simulation);

  cout << "Total de intentos : " << simulation.numOfTries << endl
       << "Total de swap : " << simulation.swap << endl
       << "total de stay : " << simulation.stay << endl
       << "Total de victorias : " << simulation.totalWin << endl;

  ConsoleInputs::ConsoleInputs::ConsoleInputs().inputTest();
  ConsoleInputs::ConsoleInputs::ConsoleInputs().inputMenu(simulation);

  cout << simulation.numberOfDoors << endl
       << simulation.numOfTries << endl
       << simulation.numberOfWiningDoors << endl
       << simulation.numberOfSwaps << endl
       << simulation.strategyType << endl;

  return EXIT_SUCCESS;
}

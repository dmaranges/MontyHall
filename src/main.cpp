#include <time.h>

#include <functional>
#include <iostream>
#include <string>

#include "ConsoleInputs.hpp"
#include "Simulator.hpp"
#include "Utils.hpp"

using namespace std;

int main(int argc, char** argv) {
  Utils::Simulation sumulation{Utils::Desition::AlwaysChange, 1000, 0, 0, 0};
  Simulator* simulator = new Simulator(5);

  simulator->startSimulation(sumulation);

  cout << "Total de intentos : " << sumulation.numOfTries << endl
       << "Total de swap : " << sumulation.swap << endl
       << "total de stay : " << sumulation.stay << endl
       << "Total de victorias : " << sumulation.totalWin << endl;

  ConsoleInputs::ConsoleInputs::ConsoleInputs().inputTest();

  return EXIT_SUCCESS;
}

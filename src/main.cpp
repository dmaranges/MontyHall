#include <time.h>

#include <functional>
#include <iostream>
#include <string>

#include "ConsoleInputs.hpp"
#include "Simulator.hpp"
#include "Utils.hpp"

using namespace std;

int main(int argc, char** argv) {
  Utils::Simulation simulation;

  ConsoleInputs::ConsoleInputs::ConsoleInputs().inputTest();
  ConsoleInputs::ConsoleInputs::ConsoleInputs().inputMenu(simulation);

  Simulator* simulator = new Simulator(std::move(simulation));
  cout << "start simulation......." << endl;
  simulator->startSimulation();

  cout << "termino la simulacion" << endl << endl;
  delete simulator;

  return EXIT_SUCCESS;
}

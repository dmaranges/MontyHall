#include <cstdlib>
#include <ctime>
#include <functional>
#include <iostream>
#include <string>

#include "ConsoleInputs.hpp"
#include "Simulator.hpp"
#include "Utils.hpp"
#include "log.hpp"

using namespace std;

int main(int argc, char** argv) {
  Utils::Simulation simulation;

  ConsoleInputs::ConsoleInputs::ConsoleInputs().inputMenu(simulation);

  Simulator* simulator = new Simulator(std::move(simulation));
  LOG_INFO("start simulation.......");
  simulator->startSimulation();

  LOG_INFO("simulation finished");
  delete simulator;

  return EXIT_SUCCESS;
}

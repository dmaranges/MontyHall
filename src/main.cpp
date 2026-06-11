#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <functional>
#include <iostream>
#include <string>

#include "Config.hpp"
#include "ConsoleInputs.hpp"
#include "Simulator.hpp"
#include "Utils.hpp"
#include "log.hpp"

using namespace std;

int main(int argc, char** argv) {
  Config::Config config =
      Config::loadConfig(std::filesystem::path("config/logger.conf"));

  Log::Config logConfig;
  logConfig.destination = config.logType == Config::LogType::Terminal
                              ? Log::Destination::Terminal
                              : Log::Destination::File;
  logConfig.filePath = config.logDirectory;

  Log::initialize(logConfig);

  Utils::Simulation simulation;

  ConsoleInputs::ConsoleInputs::ConsoleInputs().inputMenu(simulation);

  Simulator* simulator = new Simulator(std::move(simulation));
  LOG_INFO("start simulation.......");
  simulator->startSimulation();

  LOG_INFO("simulation finished");
  delete simulator;

  return EXIT_SUCCESS;
}

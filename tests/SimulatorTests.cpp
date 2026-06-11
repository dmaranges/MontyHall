// GoogleTest based simulator tests
#include <gtest/gtest.h>
#include <cstdlib>
#include <iostream>

#include "Simulator.hpp"
#include "Utils.hpp"

TEST(Simulator, ClassicSimulation) {
  Utils::Simulation sim;
  sim.numberOfDoors = 3;
  sim.numberOfWinningDoors = 1;
  sim.numberOfTries = 100;
  sim.strategyType = 2;  // AlwaysChange
  sim.typeOfSimulation = 0;

  Simulator simulator(std::move(sim));
  simulator.startSimulation();

  int wins = simulator.totalWins();
  int tries = simulator.totalTries();

  EXPECT_EQ(tries, 100);
  EXPECT_GE(wins, 0);
  EXPECT_LE(wins, tries);
}

TEST(Simulator, CustomSimulation) {
  Utils::Simulation sim;
  sim.numberOfDoors = 3;
  sim.numberOfWinningDoors = 1;
  sim.numberOfTries = 100;
  sim.numberOfSwaps = 2;
  sim.typeOfSimulation = 1;

  Simulator simulator(std::move(sim));
  simulator.startSimulation();

  int wins = simulator.totalWins();
  int tries = simulator.totalTries();

  EXPECT_EQ(tries, 100);
  EXPECT_GE(wins, 0);
  EXPECT_LE(wins, tries);
}

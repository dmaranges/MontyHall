#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include <memory>
#include <vector>

#include "Door.hpp"
#include "Utils.hpp"

class Simulator {
 public:
  Simulator(unsigned int numberOfDoors);

  ~Simulator();

  void startSimulation(Utils::Simulation& simulation);

 private:
  unsigned int nod;  // numberOfDoors
  std::vector<std::unique_ptr<Door>> doors;
};

#endif

#ifndef LOSINGDOOR_HPP
#define LOSINGDOOR_HPP

#include "Door.hpp"

class LosingDoor : public Door {
 public:
  LosingDoor() { numberOfDoors++; }
  bool winningDoor() override { return false; }
  int totalDoors() override { return numberOfDoors; }

 private:
  inline static int numberOfDoors = 0;
};

#endif

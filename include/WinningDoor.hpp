#ifndef WINNINGDOOR_HPP
#define WINNINGDOOR_HPP

#include "Door.hpp"

class WinningDoor : public Door {
 public:
  WinningDoor() { numberOfDoors++; }
  bool winningDoor() override { return true; }
  int totalDoors() override { return numberOfDoors; }

 private:
  inline static int numberOfDoors = 0;
};

#endif

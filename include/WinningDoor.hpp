#ifndef WINNINGDOOR_HPP
#define WINNINGDOOR_HPP

#include "Door.hpp"

class WinningDoor : public Door {
 public:
  bool winningDoor() override { return true; }
};

#endif

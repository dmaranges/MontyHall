#ifndef LOSINGDOOR_HPP
#define LOSINGDOOR_HPP

#include "Door.hpp"

class LosingDoor : public Door
{
public:
    bool winningDoor() override { return false; }
};

#endif

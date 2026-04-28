#include "Door.hpp"

class LosingDoor : public Door
{
public:
    bool winningDoor() override { return false; }
};

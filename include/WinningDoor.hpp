#include "Door.hpp"

class WinningDoor : public Door
{
public:
    bool winningDoor() override { return true; }
};

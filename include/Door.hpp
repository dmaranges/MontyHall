#ifndef DOOR_HPP
#define DOOR_HPP

class Door {
 public:
  virtual bool winningDoor() = 0;
  virtual ~Door() {}
};

#endif

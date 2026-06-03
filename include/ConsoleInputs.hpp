#ifndef CONSOLEINPUTS_HPP
#define CONSOLEINPUTS_HPP

#include "Utils.hpp"

namespace ConsoleInputs {

class ConsoleInputs {
 private:
  /* data */
 public:
  ConsoleInputs(/* args */) {};
  ~ConsoleInputs() {};
  void inputTest();
  void inputMenu(Utils::Simulation& simulation);
};

}  // namespace ConsoleInputs

#endif

#include "ConsoleInputs.hpp"

#include <iostream>
#include <string>
#include <vector>

// FTXUI Library
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

using namespace ftxui;

namespace ConsoleInputs {

void ConsoleInputs::inputTest() {
  Element document = hbox({
      text("left") | border,
      text("middle") | border | flex,
      text("right") | border,
  });

  auto screen = Screen::Create(Dimension::Full(), Dimension::Fit(document));
  Render(screen, document);
  screen.Print();
}

}  // namespace ConsoleInputs

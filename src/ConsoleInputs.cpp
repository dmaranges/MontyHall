#include "ConsoleInputs.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "log.hpp"

using namespace ftxui;

namespace ConsoleInputs {

bool itIsANumber(std::string& input) {
  return !input.empty() && std::all_of(input.begin(), input.end(), ::isdigit);
}

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

Component makeNumericInput(std::string* variable_str, int* variable_int) {
  Component input = Input(variable_str, "0");
  return CatchEvent(input, [variable_str, variable_int, input](Event event) {
    std::string copia = *variable_str;
    bool result = input->OnEvent(event);

    if (!variable_str->empty() && !itIsANumber(*variable_str)) {
      *variable_str = copia;
      LOG_DEBUG("Revert if letters are entered");
    } else if (!variable_str->empty()) {
      *variable_int = std::stoi(*variable_str);
      LOG_DEBUG("Update the integer");
    }
    return result;
  });
}

void ConsoleInputs::inputMenu(Utils::Simulation& simulation) {
  auto screen = ScreenInteractive::TerminalOutput();

  int actual_menu = 0;
  LOG_DEBUG("0 base, 1 Monty, 2 Custom");

  int base_selection = 0, monty_selection = 0, custom_selection = 0;
  LOG_DEBUG("Selection variables");

  std::string sNumberOfDoors = "3", sNumberOfWinningDoors = "1",
              sNumberOfTries = "1000", sNumberOfSwaps = "0",
              sStrategyType = "0";
  LOG_DEBUG("Customize simulation variables");

  LOG_DEBUG("Making Input sub-components with validation");
  Component inputNumberOfDoors =
      makeNumericInput(&sNumberOfDoors, &simulation.numberOfDoors);
  Component inputNumberOfWinningDoors = makeNumericInput(
      &sNumberOfWinningDoors, &simulation.numberOfWinningDoors);
  Component inputNumberOfTries =
      makeNumericInput(&sNumberOfTries, &simulation.numberOfTries);
  Component inputNumberOfTries2 =
      makeNumericInput(&sNumberOfTries, &simulation.numberOfTries);
  Component inputNumberOfSwaps =
      makeNumericInput(&sNumberOfSwaps, &simulation.numberOfSwaps);
  Component inputStrategyType =
      makeNumericInput(&sStrategyType, &simulation.strategyType);

  LOG_DEBUG("1. base Menu options");
  std::vector<std::string> base_options = {"Monty Hall Mode",
                                           "Custom Monty Hall Mode", "Exit"};

  auto base_menu = Menu(&base_options, &base_selection);

  LOG_DEBUG("Catch press Enter event logic");
  auto base_component = CatchEvent(base_menu, [&](Event event) {
    if (event == Event::Return) {
      if (base_selection == 0)
        actual_menu = 1;
      else if (base_selection == 1)
        actual_menu = 3;
      else
        screen.ExitLoopClosure()();
      return true;
    }
    return false;
  });

  // 2. Clasic Monty Hall Menu
  std::vector<std::string> monty_options = {"Start Simulation",
                                            "Customize statistics", "Return"};

  auto monty_menu = Menu(&monty_options, &monty_selection);
  LOG_DEBUG("2. Classic Monty Hall Menu");
  auto monty_component = CatchEvent(monty_menu, [&](Event event) {
    if (event == Event::Return) {
      if (monty_selection == 0) {
        simulation.typeOfSimulation = 0;
        screen.ExitLoopClosure()();
      };
      if (monty_selection == 1) actual_menu = 2;
      if (monty_selection == 2) {
        actual_menu = 0;
        LOG_DEBUG("return");
      }
      return true;
    }
    return false;
  });

  LOG_DEBUG("Customize statistics for Monty hall simulation");
  int clasicOptionSelected = 0;
  std::vector<std::string> clasicOptions = {"Number Of Tries", "Strategy type"};

  auto clasicMenu = Menu(&clasicOptions, &clasicOptionSelected);

  LOG_DEBUG("4. The Tab container (Right)");
  LOG_DEBUG("Shows the corresponding input according to the selected index");
  auto clasicInputsContainer = Container::Tab(
      {inputNumberOfTries2, inputStrategyType}, &clasicOptionSelected);

  LOG_DEBUG("Button to finish");
  Component clasicSaveBoton = Button("Save", [&] { actual_menu = 1; });

  auto clasicOptionsContainer = Container::Vertical(
      {Container::Horizontal({clasicMenu, clasicInputsContainer}),
       clasicSaveBoton});

  // 3. Custom Monty Hall Menu
  std::vector<std::string> custom_options = {"Start Simulation",
                                             "Customize statistics", "Return"};

  auto custom_menu = Menu(&custom_options, &custom_selection);
  LOG_DEBUG("3. Custom Monty Hall Menu");
  auto custom_component = CatchEvent(custom_menu, [&](Event event) {
    if (event == Event::Return) {
      if (custom_selection == 0) {
        simulation.typeOfSimulation = 1;
        screen.ExitLoopClosure()();
      };
      if (custom_selection == 1) actual_menu = 4;
      if (custom_selection == 2) {
        actual_menu = 0;
        LOG_DEBUG("return");
      }
      return true;
    }
    return false;
  });

  LOG_DEBUG("Customize statistics for Custom Monty hall simulation");
  int customOptionSelected = 0;
  std::vector<std::string> customOptions = {
      "Number Of Doors", "Number Of Winning Doors", "Number Of Tries",
      "Number Of Swaps"};

  auto customMenu = Menu(&customOptions, &customOptionSelected);

  LOG_DEBUG("4. The Tab container (Right)");
  LOG_DEBUG("Shows the corresponding input according to the selected index");
  auto customInputsContainer =
      Container::Tab({inputNumberOfDoors, inputNumberOfWinningDoors,
                      inputNumberOfTries, inputNumberOfSwaps},
                     &customOptionSelected);

  LOG_DEBUG("Button to finish");
  Component customSaveBoton = Button("Save", [&] { actual_menu = 3; });

  auto customOptionsContainer = Container::Vertical(
      {Container::Horizontal({customMenu, customInputsContainer}),
       customSaveBoton});

  LOG_DEBUG("TABS CONTAINER");
  auto main_container = Container::Tab(
      {
          base_component,
          monty_component,
          clasicOptionsContainer,
          custom_component,
          customOptionsContainer,
      },
      &actual_menu);

  LOG_DEBUG("Visual renderation");
  auto renderer = Renderer(main_container, [&] {
    std::string title = "";
    if (actual_menu == 0) title = "MONTY HALL SIMULATOR";
    if (actual_menu == 1) title = "CLASIC MODE";
    if (actual_menu == 2) title = "SET STATISTICS";
    if (actual_menu == 3) title = "CUSTOM MODE";
    if (actual_menu == 4) title = "SET STATISTICS";

    return vbox({text(title) | bold | center | border, filler(),
                 main_container->Render() | center, filler(),

                 hbox({text("[return] Selection | [up/down] Navegate") | dim}) |
                     border});
  });

  screen.Loop(renderer);
}

}  // namespace ConsoleInputs

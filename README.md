# Monty Hall Simulator

This repository contains a terminal-based Monty Hall simulator written in C++.
It uses an interactive console UI to let users choose between a classic Monty Hall simulation and a custom simulation with configurable parameters.

## Project Structure

- `src/main.cpp` - application entry point
- `src/ConsoleInputs.cpp` - menu and input handling using FTXUI
- `src/Simulator.cpp` - simulation engine and thread pool execution
- `include/Utils.hpp` - shared utilities and simulation configuration
- `include/Simulator.hpp` - simulator class definition
- `include/ConsoleInputs.hpp` - console input interface
- `include/Door.hpp`, `include/WinningDoor.hpp`, `include/LosingDoor.hpp` - door type abstractions

## How it works

The app launches an interactive terminal menu with two main modes:

### Classic Monty Hall Mode

This mode simulates the traditional Monty Hall problem with a fixed setup.

- The player chooses a door
- The host reveals a non-winning door
- The player either keeps the initial choice or swaps to the remaining door
- The simulation counts wins based on the selected strategy

Classic mode supports:

- random strategy (stay or swap chosen at random)
- always keep
- always change

The simulation run is controlled by the selected number of tries and strategy type.

### Custom Monty Hall Mode

This mode allows customizing the simulation parameters:

- number of doors
- number of winning doors
- number of tries
- number of swaps

Custom mode runs the simulation with the provided values and calculates total wins across the attempts.

## Running the simulator

The code is configured for CMake.

Basic usage:

```bash
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

Then run the generated executable from the `build` directory.

On launch, use the interactive menu to choose between `Monty Hall Mode` and `Custom Monty Hall Mode`.

## Notes

- `ConsoleInputs` manages the interactive menu and numeric validation.
- `Simulator` creates door instances and runs simulations using threads.
- `Utils` contains helper functions for random choice generation and result output.

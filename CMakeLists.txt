cmake_minimum_required(VERSION 4.0)
project(Montyhall VERSION 1.0)

# Usage examples:
# Configure and generate build files:
#   cmake -S . -B build -G "Visual Studio 17 2022" -A x64
# Build release executable:
#   cmake --build build --config Release
# Build the TestSimulator executable (build target named "test"):
#   cmake --build build --target test --config Release

# 1. Configure C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

# 2. Download FTXUI using FetchContent
include(FetchContent)
FetchContent_Declare(
  ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG v5.0.0  # Or the oldest version
)
FetchContent_MakeAvailable(ftxui)

# Fetch GoogleTest for unit testing
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0 # Or the oldest version
)
FetchContent_MakeAvailable(googletest)

# 3. Define source files (you can list them or use individual files)
set(SOURCES 
    src/main.cpp 
    src/Simulator.cpp 
    src/ConsoleInputs.cpp
)

# 4. Create the main executable
add_executable(Montyhall ${SOURCES})

# 5. Specify include directories for header files (.hpp)
# This allows using #include "Simulator.hpp" in .cpp files without ugly relative paths
target_include_directories(Montyhall PRIVATE include)

# 6. Link libraries (this is where linker errors like LNK2019 are resolved)
target_link_libraries(Montyhall PRIVATE 
        ftxui::screen 
        ftxui::dom 
        ftxui::component
)

add_executable(TestSimulator
    tests/SimulatorTests.cpp
    src/Simulator.cpp
)
target_include_directories(TestSimulator PRIVATE include)
target_link_libraries(TestSimulator PRIVATE GTest::gtest_main)
add_test(NAME SimulatorTests COMMAND TestSimulator)

cmake_minimum_required(VERSION 4.0)
project(Montyhall VERSION 1.0)

# 1. Configurar estándar de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 2. Descargar FTXUI usando FetchContent
include(FetchContent)
FetchContent_Declare(
  ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG v5.0.0  # O la versión más reciente
)
FetchContent_MakeAvailable(ftxui)

# 3. Definir los archivos fuentes (puedes listarlos o usar archivos individuales)
set(SOURCES 
    src/main.cpp 
    src/Simulator.cpp 
    src/Utils.cpp
)

# 4. Crear el ejecutable
add_executable(Montyhall ${SOURCES})

# 5. Indicar dónde están los archivos de cabecera (.hpp)
# Esto permite que en tus .cpp pongas #include "Simulator.hpp" sin rutas relativas feas
target_include_directories(Montyhall PRIVATE include)

# 6. Vincular las librerías (Aquí es donde se resuelven los errores LNK2019)
target_link_libraries(Montyhall PRIVATE 
    ftxui::screen 
    ftxui::dom 
    ftxui::component
)

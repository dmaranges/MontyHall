#include <time.h>
#include "Simulator.hpp"
#include "Utils.hpp"

#include <string>
#include <iostream>
#include <functional>

using namespace std;

int main(int argc, char ** argv) {
    Simulation sumulation{Desition::Aleatory, 1000, 0, 0, 0};
    Simulator *simulator = new Simulator(3);

    simulator->startSimulation(sumulation);

    cout << "Total de intentos : " << sumulation.numOfTries << endl
         << "Total de swap : " << sumulation.swap << endl
         << "total de stay : " << sumulation.stay << endl
         << "Total de victorias : " << sumulation.totalWin << endl;

    return EXIT_SUCCESS;
}

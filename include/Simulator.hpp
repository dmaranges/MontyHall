#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include <vector>
#include <memory>
#include "Door.hpp"
#include "Utils.hpp"

class Simulator
{
    public:
        Simulator(unsigned int numberOfDoors);

        ~Simulator();

        void startSimulation(Simulation& simulation);

    private:
        unsigned int nod; //numberOfDoors
        std::vector<std::unique_ptr<Door>> doors;

};

#endif

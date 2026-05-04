#ifndef UTILS_HPP
#define UTILS_HPP

#include <stdlib.h>
#include <iostream>
#include <random>

#define log(s) (std::cout << s << endl)

using namespace std;

enum Desition {
    Aleatory,
    AlwaysKeep,
    AlwaysChange
};

struct Simulation
{
        Desition desition; // Type of selection (swap or stay) "0 = random", "1 = stay", "2 = swap"
        int numOfTries; // Quantity of tries to simulate
        int totalWin; // Quantity of wins

        int stay; // Save the number of situations where swaps the selection.
        int swap; // Save the number of situations where stays the selection.
};

inline int getRandomBool () {
    static std::random_device rd; 
    static std::mt19937 gen(rd());
    static std::bernoulli_distribution d(0.5); // 0.5 probability for true
    return d(gen);
}

inline int getRandomChose (int minValue, int maxValue) {
    // 1. Obtain a random seed from hardware
    std::random_device rd; 
    // 2. Initialize the generator engine (Mersenne Twister) with the seed
    std::mt19937 gen(rd());
    // 3. Define the range [min, max] (e.g., 1 to 100 inclusive)
    std::uniform_int_distribution<> distrib(minValue, maxValue - 1); 

    // 4. Generate the number
    return distrib(gen);
}

#endif
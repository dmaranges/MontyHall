#ifndef UTILS_HPP
#define UTILS_HPP

#include <stdlib.h>
#include <iostream>

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


/*********************************************************************************
 * Return a random value between min and max value.
*********************************************************************************/
int giveRandRange(int minV, int maxV);

/*********************************************************************************
 * Return a random value between one and three.
*********************************************************************************/
int giveRandOneToThre();

/*********************************************************************************
 * Return a random value between one and two.
*********************************************************************************/
int oneOrTwo();

/*********************************************************************************
 * Return the int value from string conversion. Return -1 in error case.
*********************************************************************************/
int checkInput(string str);

/*********************************************************************************
 * Print in console the help description for --help argument.
*********************************************************************************/
void printHelp(string arg);

/*********************************************************************************
 * Return true if inputs are different.
*********************************************************************************/
template <typename T>
bool notEq(T a, T b)
{
    return a != b;
}

/*********************************************************************************
 * Return true if inputs are the same.
*********************************************************************************/
template <typename T>
bool isEq(T a, T b)
{
    return a == b;
}

#endif
#ifndef UTILS_HPP
#define UTILS_HPP

#include <stdlib.h>
#include <iostream>

#define _int int
#define log(s) (std::cout << s << endl)

using namespace std;

/*********************************************************************************
 * Return a random value between min and max value.
*********************************************************************************/
_int giveRandRange(_int minV, _int maxV);

/*********************************************************************************
 * Return a random value between one and three.
*********************************************************************************/
_int giveRandOneToThre();

/*********************************************************************************
 * Return a random value between one and two.
*********************************************************************************/
_int oneOrTwo();

/*********************************************************************************
 * Return the int value from string conversion. Return -1 in error case.
*********************************************************************************/
_int checkInput(string str);

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
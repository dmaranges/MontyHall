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
 * Return true if inputs are different.
*********************************************************************************/
bool notEq(_int a, _int b);

/*********************************************************************************
 * Return true if inputs are the same.
*********************************************************************************/
bool isEq(_int a, _int b);

/*********************************************************************************
 * Return the int value from string conversion. Return -1 in error case.
*********************************************************************************/
_int checkInput(string str);

/*********************************************************************************
 * Print in console the help description for --help argument.
*********************************************************************************/
void printHelp(string arg);

#endif
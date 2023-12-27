#ifndef UTILS_HPP
#define UTILS_HPP

#include <stdlib.h>
#include <iostream>

#define _int int

using namespace std;

/*********************************************************************************
 * Return a random valure from a min value to a max value
*********************************************************************************/
_int giveRandRange(_int minV, _int maxV);

/*********************************************************************************
 * Return a random valure between one and thre.
*********************************************************************************/
_int giveRandOneToThre();

/*********************************************************************************
 * Return one or two random.
*********************************************************************************/
_int oneOrTwo();

/*********************************************************************************
 * Return true if ints are different.
*********************************************************************************/
bool notEq(_int a, _int b);

/*********************************************************************************
 * Return true if ints are the same.
*********************************************************************************/
bool isEq(_int a, _int b);

/*********************************************************************************
 * Return the int value from string convertion. Return -1 in error case.
*********************************************************************************/
_int checkInput(string str);

/*********************************************************************************
 * Print in console the help description for --help argument.
*********************************************************************************/
void printHelp(string arg);

#endif
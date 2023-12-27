#ifndef UTILS_HPP
#define UTILS_HPP

#include <stdlib.h>
#include <iostream>

#define _int int

using namespace std;

_int giveRandTries(_int minV, _int maxV);

_int giveRandSelection();

_int oneOrTwo();

bool notEq(_int a, _int b);

bool isEq(_int a, _int b);

_int checkInput(string str);

void printHelp(string arg);

#endif
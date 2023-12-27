#include "../include/Utils.hpp"

#include <string>

_int giveRandTries(_int minV, _int maxV) {    
    return minV + (rand() % (maxV - minV));
}

_int giveRandSelection() {
    _int selection = (rand() % 30);

    if (selection < 10)
    {
        return 1;
    }
    else if (selection < 20)
    {
        return 2;
    }
    
    return 3;
}

_int oneOrTwo() {
    _int selection = (rand() % 20);

    return selection < 10 ?  1 : 2;
}

bool notEq(_int a, _int b)
{
    return a != b;
}

bool isEq(_int a, _int b)
{
    return a == b;
}

_int checkInput(string str)
{
    cout << str << endl;
    _int inpValue = -1;
    try
    {
        inpValue = stoi(str);
        if (inpValue < 0)
            cout << "[ERROR] wrong input: " << str << endl;
    }
    catch(const std::exception& e)
    {
        cout << "[ERROR] wrong input: " << str << endl;
    }
    return inpValue;
}

void printHelp(string arg)
{
    cout << endl << "Syntax: " << endl
         << arg << endl
         << "\"type of selection (random for default)\"" << endl
         << "\"number of tries (between 1 and " << INT_MAX << ", random by default)\"" << endl
         << "\"number of simulations (1 by default)\"" << endl << endl
         << "example: " << arg << " 1 1000 1" << endl << endl;
}

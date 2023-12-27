#include "../include/Utils.hpp"

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

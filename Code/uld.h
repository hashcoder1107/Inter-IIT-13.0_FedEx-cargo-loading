#ifndef ULD_H
#define ULD_H

#include <bits/stdc++.h>
using namespace std;

class ULD{
    public:
    int uldIdentifier, length, width, height, weightLimit;

    ULD(int uldIdentifier, int length, int width, int height, int weightLimit){
        this->uldIdentifier = uldIdentifier;
        this->length = length;
        this->width = width;
        this->height = height;
        this->weightLimit = weightLimit;
    }
};

#endif 
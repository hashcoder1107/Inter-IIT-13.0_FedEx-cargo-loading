#ifndef PACKAGE_H
#define PACKAGE_H

#include <bits/stdc++.h>
using namespace std;

class PACKAGE
{
public:
    int packageIdentifier, length, width, height, weight, delayCost;
    bool priority; // Indicates whether package is of type priority or economy. 1 -> Priority and 0 -> Economy

    PACKAGE(int packageIdentifier, int length, int width, int height, int weight, int delayCost, bool priority)
    {
        this->packageIdentifier = packageIdentifier;
        this->length = length;
        this->width = width;
        this->height = height;
        this->weight = weight;
        this->priority = priority;
        this->delayCost = delayCost;
    }

    PACKAGE()
    {
        this->packageIdentifier = 0;
        this->length = 0;
        this->width = 0;
        this->height = 0;
        this->weight = 0;
        this->priority = false;
        this->delayCost = 0;
    }
};

#endif
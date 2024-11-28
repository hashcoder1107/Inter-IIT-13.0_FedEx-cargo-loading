#include <bits/stdc++.h>
using namespace std;
#define init 0
#ifndef PACKAGE_H
#define PACKAGE_H

class packages{
    public:
    int identifier, length, width, height, weight, delayCost;
    bool priority;

    packages(){
        identifier=init, length=init; width=init; height=init; weight=init; delayCost=init;
        priority=false;
    }
};

#endif 
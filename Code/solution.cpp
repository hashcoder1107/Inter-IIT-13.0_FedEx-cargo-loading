#include<bits/stdc++.h>
#include "parser.h"
#include "package.h"
#include "uld.h"
using namespace std;


int main(){

    int uldPriorityPenalty = 0;
    vector<PACKAGE> packages;
    vector<ULD> ulds;
    parseInput(uldPriorityPenalty, packages, ulds);


    // Display parsed data
    cout << endl << "K: ";
    cout << uldPriorityPenalty << endl;
    cout << endl;
    cout << "Parsed Package Data:" << endl;
    for (const auto& pkg : packages) {
        cout << "ID: " << pkg.packageIdentifier  << ", Dimensions: " << pkg.length << "x" << pkg.width << "x" << pkg.height << ", Weight: " << pkg.weight << "kg, Type: " << pkg.priority << ", Cost of Delay: " << pkg.delayCost << endl;
    }
    cout << endl;
    cout << "ULD Data:" << endl;
    for (const auto& uld : ulds) {
        cout << "ID: " << uld.uldIdentifier  << ", Dimensions: " << uld.length << "x" << uld.width << "x" << uld.height << ", Weight: " << uld.weightLimit << "kg" << endl;
    }
}
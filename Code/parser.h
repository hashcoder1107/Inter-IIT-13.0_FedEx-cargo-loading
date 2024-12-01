#ifndef PARSER_H
#define PARSER_H

#include <bits/stdc++.h>
#include "package.h"
#include "uld.h"
using namespace std;

#define PRIORITY_DELAY_COST 1000000000

PACKAGE parsePackageInput(const string& inputRow){
    stringstream stringStreamObject(inputRow);
    // String holders for parsed data
    string _packageIdentifier, _length, _width, _height, _weight, _priority, _delayCost;
    // Variables to hold the parsed data once typecasted to their respective data type
    int packageIdentifier, length, width, height, weight, delayCost;
    bool priority = false;

    // Fetched the Identifier, Dimensions, Weight, Type(Priority/Economy), cost of delay one at a time
    getline(stringStreamObject, _packageIdentifier, ',');
    packageIdentifier = stoi(_packageIdentifier.substr(2));

    getline(stringStreamObject, _length, ',');
    length = stoi(_length);

    getline(stringStreamObject, _width, ',');
    width = stoi(_width);

    getline(stringStreamObject, _height, ',');
    height = stoi(_height);

    getline(stringStreamObject, _weight, ',');
    weight = stoi(_weight);

    getline(stringStreamObject, _priority, ',');
    if(_priority[0] == 'P' || _priority[0] == 'p') priority = true;

    getline(stringStreamObject, _delayCost, ',');
    if(_delayCost != "-") delayCost = stoi(_delayCost);
    else delayCost = PRIORITY_DELAY_COST;

    // Prepared a package object with the fetched details to return
    PACKAGE pkg(packageIdentifier, length, width, height, weight, delayCost, priority);
    return pkg;
}

ULD parseUldInput(const string& inputRow) {
    stringstream stringStreamObject(inputRow);
    // String holders for parsed data
    string _uldIdentifier, _length, _width, _height, _weightLimit;
    // Variables to hold the parsed data once typecasted to their respective data type
    int uldIdentifier, length, width, height, weightLimit;

    // Fetched the Identifier, Dimensions, Weight Limit one at a time
    getline(stringStreamObject, _uldIdentifier, ',');
    uldIdentifier = stoi(_uldIdentifier.substr(1));

    getline(stringStreamObject, _length, ','); 
    length = stoi(_length);

    getline(stringStreamObject, _width, ','); 
    width = stoi(_width);

    getline(stringStreamObject, _height, ','); 
    height = stoi(_height);

    getline(stringStreamObject, _weightLimit, ','); 
    weightLimit = stoi(_weightLimit);
    
    // Prepared a uld object with the fetched details to return
    ULD uld(uldIdentifier, length, width, height, weightLimit);
    return uld;
}

void parseInput(int& uldPriorityPenalty, vector<PACKAGE>& packages, vector<ULD>& ulds){

    PACKAGE dummyPackage;
    packages.push_back(dummyPackage);

    ULD dummyULD;
    ulds.push_back(dummyULD);
    
    ifstream inputFile("../Input/input.txt");
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open the file." << endl;
        return ;
    }

    string inputRow;

    // Parse the file line by line
    while (getline(inputFile, inputRow)){
        if(inputRow.length() == 0) continue;
        if(inputRow[0] == 'P' || inputRow[0] == 'p'){
            // Parsing the package details and populate the packages with the parsed data
            packages.push_back(parsePackageInput(inputRow));
        }
        else if(inputRow[0] == 'U' || inputRow[0] == 'u'){
            // Parsing the uld details and populate the ulds with the parsed data
            ulds.push_back(parseUldInput(inputRow));
        }
        else{
            uldPriorityPenalty = stoi(inputRow);
        }
    }
    inputFile.close();
}

#endif

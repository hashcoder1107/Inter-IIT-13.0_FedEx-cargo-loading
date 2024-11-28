// Input.txt -> Parse -> VECTOR<ULD>,VECTOR<PACKAGE> -> SOLUTION.CPP
#include <bits/stdc++.h>
using namespace std;
#include "package.h"
#include "uld.h"

Package parseLine(const string& line) {
    stringstream ss(line);
    string temp;
    Package pkg;

    getline(ss, pkg.identifier, ',');
    getline(ss, temp, ','); pkg.length = stoi(temp);
    getline(ss, temp, ','); pkg.width = stoi(temp);
    getline(ss, temp, ','); pkg.height = stoi(temp);
    getline(ss, temp, ','); pkg.weight = stoi(temp);
    getline(ss, pkg.type, ',');
    getline(ss, temp, ','); pkg.costOfDelay = stoi(temp);

    return pkg;
}

// Main function
int main() {
    ifstream inputFile("package.csv");
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open the file." << endl;
        return 1;
    }

    string line;
    vector<Package> packages;

    // Skip the header line
    getline(inputFile, line);

    // Parse the file line by line
    while (getline(inputFile, line)) {
        packages.push_back(parseLine(line));
    }
    inputFile.close();

    // Display parsed data
    cout << "Parsed Package Data:" << endl;
    for (const auto& pkg : packages) {
        cout << "ID: " << pkg.identifier 
             << ", Dimensions: " << pkg.length << "x" << pkg.width << "x" << pkg.height 
             << ", Weight: " << pkg.weight 
             << "kg, Type: " << pkg.type 
             << ", Cost of Delay: " << pkg.costOfDelay << endl;
    }

    return 0;
}


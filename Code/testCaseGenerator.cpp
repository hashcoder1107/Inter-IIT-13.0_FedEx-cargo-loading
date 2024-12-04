#include <bits/stdc++.h>
#include <fstream>
using namespace std;
#define FILE_PATH "Input/generatedInput.txt"

// Generates random input testcases for comparison of different solutions

void generateK(ofstream &outputFile,int minK,int maxK)
{
    // Chooses random K uniformly distributed in range [minK,maxK]
    int k = minK + (rand()) % (maxK - minK + 1);
    outputFile << k << endl << endl;
}

void generateULDs(ofstream &outputFile, int numUld, int maxUldDimension, int maxUldWeight)
{
    // Generating random values for all ULD length,breadth and height parameters , in range [1,maxUldDimension] , and range [1,maxUldWeight] for maximum weight limit parameter
    for (int uldIdentifier = 1; uldIdentifier <= numUld; uldIdentifier++)
    {
        int uldLength = (rand() % maxUldDimension) + 1;
        int uldWidth = (rand() % maxUldDimension) + 1;
        int uldHeight = (rand() % maxUldDimension) + 1;
        int uldWeightLimit = (rand() % maxUldWeight) + 1;

        outputFile << "U" << uldIdentifier << "," << uldLength << "," << uldWidth << "," << uldHeight << "," << uldWeightLimit << endl;
    }

    outputFile << endl;
}

void generatePackages(ofstream &outputFile, int numPackage, int maxPackageDimension, int maxPackageWeight, int numPriorityPackage , int minCost, int maxCost)
{
    // Generating random values for all Package length,breadth and height parameters , in range [1,maxUldDimension] , and range [1,maxPackageWeight] for package weight parameter

    int priorityCounter = 0;
    for (int packageIdentifier = 1; packageIdentifier <= numPackage; packageIdentifier++)
    {
        int packageLength = (rand() % maxPackageDimension) + 1;
        int packageWidth = (rand() % maxPackageDimension) + 1;
        int packageHeight = (rand() % maxPackageDimension) + 1;
        int packageWeight = (rand() % maxPackageWeight) + 1;

        bool priority;

        // Setting priority parameter value of current package randomly , based on number of remaining priority packages to be assigned

        int numRemainingPackage = numPackage - packageIdentifier + 1;
        int numRemainingPriorityPackage = numPriorityPackage - priorityCounter;

        if(rand() % numRemainingPackage < numRemainingPriorityPackage){
            priority = true;
            priorityCounter++;
        }
        else{
            priority = false;
        }

        // if ((numPackage - packageIdentifier + 1) > (numPriorityPackages - priorityCounter) && (priorityCounter < numPriorityPackages))
        // {
        //     priority = (rand() % 2);
        //     if (priority)
        //     {
        //         priorityCounter++;
        //     }
        // }
        // else if (priorityCounter == numPriorityPackages)
        // {
        //     priority = false;
        // }
        // else
        // {
        //     priority = true;
        //     priorityCounter++;
        // }

        outputFile << "P-" << packageIdentifier << "," << packageLength << "," << packageWidth << "," << packageHeight << "," << packageWeight;
        if (priority)
        {
            outputFile << ",Priority,-" << endl;
        }
        else
        {
            outputFile << ",Economy,";
            // Generating delay cost in range [minCost,maxCost]
            int costOfDelay = minCost + rand()%(maxCost - minCost + 1);
            outputFile << costOfDelay << endl;
        }
    }
}

int main(int argc,char* argv[])
{
    ofstream outputFile(FILE_PATH);
    if (!outputFile) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    srand(time(0)); 

    int minK = atoi(argv[1]); // Min value of K
    int maxK = atoi(argv[2]); // Max value of K
    int numUld = atoi(argv[3]); // Number of ULDs
    int maxUldDimension = atoi(argv[4]); // Max ULD Length/Width/height
    int maxUldWeight = atoi(argv[5]); // Max ULD Weight
    int numPackage = atoi(argv[6]); // Number of Packages
    int maxPackageDimension = atoi(argv[7]); // Max Package Length/Width/height
    int maxPackageWeight = atoi(argv[8]); // Max Package Weight
    double priorityPercent = atof(argv[9]); // Desired percentage of priority packages
    int minCost = atoi(argv[10]); // Minimum delay cost
    int maxCost = atoi(argv[11]); // Maximum delay cost

    generateK(outputFile,minK,maxK);
    generateULDs(outputFile, numUld, maxUldDimension, maxUldWeight);
    generatePackages(outputFile, numPackage, maxPackageDimension, maxPackageWeight, (int)(priorityPercent*numPackage), minCost, maxCost);

    outputFile.close(); // Close the file
}
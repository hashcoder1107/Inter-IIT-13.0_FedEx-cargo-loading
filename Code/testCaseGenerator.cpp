#include <bits/stdc++.h>
#include <fstream>
using namespace std;

void generateK(ofstream &outputFile)
{
    int k = 1000 + (rand()) % 5000;
    outputFile << k << endl
               << endl;
}

void generateULDs(ofstream &outputFile, int numberOfULDs, int maximumULDDimension, int maximumWeightLimit)
{
    for (int uldIdentifier = 1; uldIdentifier <= numberOfULDs; uldIdentifier++)
    {
        int uldLength = (rand() % maximumULDDimension) + 1;
        int uldWidth = (rand() % maximumULDDimension) + 1;
        int uldHeight = (rand() % maximumULDDimension) + 1;
        int uldWeightLimit = (rand() % maximumWeightLimit) + 1;

        outputFile << "U" << uldIdentifier << "," << uldLength << "," << uldWidth << "," << uldHeight << "," << uldWeightLimit << endl;
    }

    outputFile << endl;
}

void generatePackages(ofstream &outputFile, int numberOfPackages, int maximumPackageDimension, int maximumWeight, int numberOfPriorityPackages)
{
    int priorityCounter = 0;
    for (int packageIdentifier = 1; packageIdentifier <= numberOfPackages; packageIdentifier++)
    {
        int packageLength = (rand() % maximumPackageDimension) + 1;
        int packageWidth = (rand() % maximumPackageDimension) + 1;
        int packageHeight = (rand() % maximumPackageDimension) + 1;
        int packageWeight = (rand() % maximumWeight) + 1;

        bool priority;
        if ((numberOfPackages - packageIdentifier + 1) > (numberOfPriorityPackages - priorityCounter) && (priorityCounter < numberOfPriorityPackages))
        {
            priority = (rand() % 2);
            if (priority)
            {
                priorityCounter++;
            }
        }
        else if (priorityCounter == numberOfPriorityPackages)
        {
            priority = false;
        }
        else
        {
            priority = true;
            priorityCounter++;
        }

        outputFile << "P-" << packageIdentifier << "," << packageLength << "," << packageWidth << "," << packageHeight << "," << packageWeight;
        if (priority)
        {
            outputFile << ",Priority,-" << endl;
        }
        else
        {
            outputFile << ",Economy,";
            int costOfDelay = ((1 + rand() % 10) * 100);
            outputFile << costOfDelay << endl;
        }
    }
}

int main()
{
    srand(time(0));

    int numberOfULDs;
    cout << "Enter the number of ULDs you want: " << endl;
    cin >> numberOfULDs;

    int maximumULDDimension;
    cout << "Enter the maximum value the dimensions of ULD can achieve in any of the 3 axes: " << endl;
    cin >> maximumULDDimension;

    int maximumWeightLimit;
    cout << "Enter the maximum value of the weightLimit that ULDs can achieve: " << endl;
    cin >> maximumWeightLimit;

    int numberOfPackages;
    cout << "Enter the number of Packages you want: " << endl;
    cin >> numberOfPackages;

    int maximumPackageDimension;
    cout << "Enter the maximum value the dimensions of packages can achieve in any of the 3 axes: " << endl;
    cin >> maximumPackageDimension;

    int maximumWeight;
    cout << "Enter the maximum value of the weight that any package can achieve: " << endl;
    cin >> maximumWeight;

    int numberOfPriorityPackages;
    cout << "Enter the number of priority packages you want: " << endl;
    cin >> numberOfPriorityPackages;

    ofstream outputFile("../Input/generatedInput.txt");
    if (!outputFile)
    {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    generateK(outputFile);
    generateULDs(outputFile, numberOfULDs, maximumULDDimension, maximumWeightLimit);
    generatePackages(outputFile, numberOfPackages, maximumPackageDimension, maximumWeight, numberOfPriorityPackages);

    outputFile.close(); // Close the file
}

// 3 100 100 10 50 50 5
// 6 1000 5000 300 50 100 100
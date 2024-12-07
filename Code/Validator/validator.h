#ifndef VALIDATOR_H
#define VALIDATOR_H

#include "../uld.h"
#include "../package.h"
#include "../output.h"
#include "../parser.h"
#include "../Solution/Solution.h"
using namespace std;

bool validate(vector<ULD> &uldInfo, vector<PACKAGE> &packagesInfo, Solution &sol, int &k)
{
    int numUld = uldInfo.size();
    int mxUldDim = 0;
    for (auto uld : uldInfo)
    {
        if (uld.uldIdentifier)
        {
            mxUldDim = max({mxUldDim, uld.height, uld.width, uld.length});
        }
    }

    vector<vector<vector<int>>> table(numUld, vector<vector<int>>(mxUldDim, vector<int>(mxUldDim, -1)));
    map<int, int> uldWeightSum;

    auto _packages = sol.getPackages();
    auto packages = vector<pair<int, AssignedPackage>>(_packages.begin(), _packages.end());

    sort(packages.begin(), packages.end(), [&](pair<int, AssignedPackage> left, pair<int, AssignedPackage> right)
         {  
            int z1 = get<2>(left.second.bottomLeft);
            int z2 = get<2>(right.second.topRight);

            return z1 < z2; });

    for (auto t : sol.getPackages())
    {
        auto package = t.second;
        int uldId = package.assignedUld;
        if (uldId == -1)
        {
            if (package.isPriority)
            {
                cout << "Unused Priority: " << package.packageId << endl;
                return false;
            }
            continue;
        }

        ULD assignedUld;
        for (auto uld : uldInfo)
        {
            if (uld.uldIdentifier == uldId)
                assignedUld = uld;
        }

        // Weight
        uldWeightSum[uldId] += package.weight;
        if (uldWeightSum[uldId] > assignedUld.weightLimit)
        {
            cout << "Weight Limit: " << uldId << ' ' << uldWeightSum[uldId] << endl;
            return false;
        }

        // Volume
        int x1 = get<0>(package.bottomLeft);
        int y1 = get<1>(package.bottomLeft);
        int z1 = get<2>(package.bottomLeft);

        int x2 = get<0>(package.topRight);
        int y2 = get<1>(package.topRight);
        int z2 = get<2>(package.topRight);
        ;

        for (int i = x1; i < x2; i++)
        {
            for (int j = y1; j < y2; j++)
            {
                if (table[uldId][i][j] >= z1)
                {
                    cout << "Overlap: " << package.packageId << endl;
                    return false;
                }
                else
                {
                    table[uldId][i][j] = z2;
                }
            }
        }

        return true;
    }

    return true;
    // vector<vector<vector<int>>> uldBaseMatrix;
    // initialise(uldBaseMatrix, uldInfo);

    // sort(solnOutput.outputRows.begin(), solnOutput.outputRows.end(), comparator); // sorted using manual comparator

    // solnOutput.print();

    // if (allPriorityPackagesTaken(packagesInfo, solnOutput) && boundaryCheck(uldInfo, solnOutput) && overlapCheck(uldInfo, uldBaseMatrix, solnOutput) && weightCheck(uldInfo, packagesInfo, solnOutput))
    // {
    //     cout << "Given solution passes all 4 parameters" << endl;
    //     cout << "Total Cost is: " << costFunction(uldInfo, packagesInfo, solnOutput, k) << endl;
    // }
}

#endif
#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <bits/stdc++.h>
#include "uld.h"
#include "package.h"
#include "output.h"
#include "parser.h"
using namespace std;

void initialise(vector<vector<vector<int>>>& uldBaseMatrix, vector<ULD>& uldInfo){
    int uldCount = uldInfo.size();
    uldBaseMatrix.resize(uldCount);
    for(int i=1; i<uldCount; i++){
        uldBaseMatrix[i].resize(uldInfo[i].length+1, vector<int>(uldInfo[i].width+1, 0));
    }
}

static bool comparator(OUTPUT_ROW &package1,OUTPUT_ROW &package2){
    //Sorting initially on the basis of ULDNo. assigned to a paritcular package
    if( package1.uldNumber < package2.uldNumber) return true;
    else if( package1.uldNumber > package2.uldNumber) return false;
    else{
        //If same ULDNumber then sort on the basis of z-cordinate of bottomLeft
        if(package1.bottomLeft[2] < package2.bottomLeft[2]) return true;
        return false;
    }
}

bool allPriorityPackagesTaken(vector<PACKAGE>& packagesInfo, OUTPUT& solnOutput){
    bool allPriorityTakenFlag=true;

    for(int index=1 ; index < solnOutput.outputRows.size() ; index++){
        if(solnOutput.outputRows[index].uldNumber==-1 && packagesInfo[solnOutput.outputRows[index].packageNumber].priority){
            allPriorityTakenFlag&=false;

            cout<<"Package number: "<<solnOutput.outputRows[index].packageNumber<<" is a PRIORITY package but it has not been taken"<<endl;
            return allPriorityTakenFlag;
        }
        else if(solnOutput.outputRows[index].uldNumber!=-1){
            break;
        }
    }

    return allPriorityTakenFlag;
}

bool boundaryCheck(vector<ULD>& uldInfo, OUTPUT& solnOutput){

    bool boundaryFlag=true;
    int index=1;
    while(index<solnOutput.outputRows.size() && solnOutput.outputRows[index].uldNumber==-1){ //skips the packages that are not assigned to any ULD
        index++;
    }

    for(index ; index < solnOutput.outputRows.size() ; index++){
        vector <int> ULDBottomLeft (3,0);
        vector <int> ULDTopRight (3,0);

        int ULDNumber=solnOutput.outputRows[index].uldNumber;
        ULDTopRight[0]=uldInfo[ULDNumber].length;
        ULDTopRight[1]=uldInfo[ULDNumber].width;
        ULDTopRight[2]=uldInfo[ULDNumber].height;

        if(solnOutput.outputRows[index].bottomLeft[0] < 0 || solnOutput.outputRows[index].bottomLeft[1] < 0 || solnOutput.outputRows[index].bottomLeft[2] < 0){
            cout<<"bottomLeft of package "<<solnOutput.outputRows[index].packageNumber<<" is outside ULD to the bottomLeft End "<<ULDNumber<<endl;
            boundaryFlag&=false;
            return boundaryFlag;
        }

        if(solnOutput.outputRows[index].bottomLeft[0] > ULDTopRight[0] || solnOutput.outputRows[index].bottomLeft[1] > ULDTopRight[1] || solnOutput.outputRows[index].bottomLeft[2] > ULDTopRight[2]){
            cout<<"bottomLeft of package "<<solnOutput.outputRows[index].packageNumber<<" is outside ULD to the topRight End "<<ULDNumber<<endl;
            boundaryFlag&=false;
            return boundaryFlag;
        }

        if(solnOutput.outputRows[index].topRight[0]>ULDTopRight[0] || solnOutput.outputRows[index].topRight[1]>ULDTopRight[1] || solnOutput.outputRows[index].topRight[2]>ULDTopRight[2]){
            cout<<"topRight of package "<<solnOutput.outputRows[index].packageNumber<<" is outside ULD to the topRight End "<<ULDNumber<<endl;
            boundaryFlag&=false;
            return boundaryFlag;
        }        

        if(solnOutput.outputRows[index].topRight[0] < 0 || solnOutput.outputRows[index].topRight[1] < 0 || solnOutput.outputRows[index].topRight[2] < 0){
            cout<<"bottomLeft of package "<<solnOutput.outputRows[index].packageNumber<<" is outside ULD to the bottomLeft End "<<ULDNumber<<endl;
            boundaryFlag&=false;
            return boundaryFlag;
        }
    }

    return boundaryFlag;
}

bool overlapCheck(vector<ULD>& uldInfo, vector<vector<vector<int>>>& uldBaseMatrix, OUTPUT& solnOutput){
    for(int index = 1; index<solnOutput.outputRows.size(); index++){
        if(solnOutput.outputRows[index].uldNumber == -1) continue;
        int uldNumber = solnOutput.outputRows[index].uldNumber;
        int packageNumber = solnOutput.outputRows[index].packageNumber;

        vector<int> bottomLeft = solnOutput.outputRows[index].bottomLeft;
        vector<int> topRight = solnOutput.outputRows[index].topRight;

        int supportAvailable = 0;

        for(int i=bottomLeft[0]; i<=topRight[0]; i++){
            for(int j=bottomLeft[1]; j<=topRight[1]; j++){
                if(uldBaseMatrix[uldNumber][j][i] > bottomLeft[2]){
                    cout << "Package Number " << packageNumber << " stored in ULD Number " << uldNumber << " is overlapping." << endl;
                    return false;
                }
                if(bottomLeft[2] == 0 || uldBaseMatrix[uldNumber][j][i] == bottomLeft[2]){
                    supportAvailable++;
                }
            }
        }

        double percentageSupport = (((double)supportAvailable)/((topRight[0]-bottomLeft[0]+1)*(topRight[1]-bottomLeft[1]+1)))*100;
        cout << "Package Number " << packageNumber << " has a support of " << percentageSupport << " % " << endl;

        for(int i=bottomLeft[0]; i<=topRight[0]; i++){
            for(int j=bottomLeft[1]; j<=topRight[1]; j++){
                uldBaseMatrix[uldNumber][j][i] = topRight[2];
            }
        }
    }
   return true;
}

bool weightCheck(vector<ULD>& uldInfo, vector<PACKAGE>& packagesInfo, OUTPUT& solnOutput){
    vector<int> uldWeights(uldInfo.size(),0);

    int index=1;
    while(index<solnOutput.outputRows.size() && solnOutput.outputRows[index].uldNumber==-1){ //skips the packages that are not assigned to any ULD
        index++;
    }

    for(index;index<solnOutput.outputRows.size();index++){
        uldWeights[solnOutput.outputRows[index].uldNumber]+=packagesInfo[solnOutput.outputRows[index].packageNumber].weight;
    }

    set<int> uldsWeightLimitExceeded;

    for(int i=1;i<uldInfo.size();i++){
        if(uldWeights[uldInfo[i].uldIdentifier]>uldInfo[i].weightLimit){
            uldsWeightLimitExceeded.insert(uldInfo[i].uldIdentifier);
        }
    }

    if(uldsWeightLimitExceeded.size()==0){
        return true;
    }

    cout<<"ULDs where weight limits were crossed are: ";
    for(auto it:uldsWeightLimitExceeded){
        cout<<it<<" ";
    }
    cout<<endl;

    return false;
}

int costFunction(vector<ULD>& uldInfo, vector<PACKAGE>& packagesInfo, OUTPUT& solnOutput,int &k){
    vector<bool> hasPriority(uldInfo.size(),false);
    int totalCost=0;

    int index=1;
    int costDueToEconomy=0;
    while(index<solnOutput.outputRows.size() && solnOutput.outputRows[index].uldNumber==-1){ //Calculate cost of economy packages that are left behind
        costDueToEconomy+=packagesInfo[solnOutput.outputRows[index].packageNumber].delayCost;
        index++;
    }
    totalCost+=costDueToEconomy;

    for(index;index<solnOutput.outputRows.size();index++){
        if(packagesInfo[solnOutput.outputRows[index].packageNumber].priority){
            hasPriority[solnOutput.outputRows[index].uldNumber]=true;
        }
    }

    int ULDsHavingPriorityPackages=0;
    for(int i=1;i<uldInfo.size();i++){
        if(hasPriority[uldInfo[i].uldIdentifier]){
            ULDsHavingPriorityPackages++;
        }
    }

    int costDueToPriority=(k*ULDsHavingPriorityPackages);
    totalCost+=costDueToPriority;
    return totalCost;
}

int validate(vector<ULD>& uldInfo, vector<PACKAGE>& packagesInfo, OUTPUT& solnOutput,int &k){
    vector<vector<vector<int>>> uldBaseMatrix;
    initialise(uldBaseMatrix, uldInfo);

    sort(solnOutput.outputRows.begin(),solnOutput.outputRows.end(),comparator); //sorted using manual comparator

    if(allPriorityPackagesTaken(packagesInfo,solnOutput) && boundaryCheck(uldInfo,solnOutput) && overlapCheck(uldInfo,uldBaseMatrix,solnOutput) && weightCheck(uldInfo,packagesInfo,solnOutput)){
        cout<<"Given solution passes all 4 parameters"<<endl;
        cout<<"Total Cost is: "<<costFunction(uldInfo,packagesInfo,solnOutput,k)<<endl;
    }

    return 0;
}

#endif
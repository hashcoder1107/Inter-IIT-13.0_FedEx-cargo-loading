#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <tuple>
#include <functional>
#include "uld.h"
#include "package.h"
#include "output.h"
#include "parser.h"
#include "validator.h"
#include <cmath>
#include "RMQ.h"
using namespace std;

#define INF 1e9
#define ALPHA 5587.836
#define BETA 5975.6536

void print2(tuple<int,int,int> t,int x = 0){
    cout<<get<0>(t)-x<<",";
    cout<<get<1>(t)-x<<",";
    cout<<get<2>(t)-x;
    cout<<"\n";
}

class ULDBaseMatrix{
    private:
        // vector<vector<int>> Matrix;
        MaxSumQuery2D Matrix;
        int length,width,height;
        int maxWeightLimit,curWeight;
        int uldIdentifier;

    public:
        // Initialises ULD Matrix
        ULDBaseMatrix(ULD u){
            length=u.length;
            width=u.width;
            height=u.height;
            maxWeightLimit=u.weightLimit;
            curWeight=0;
            uldIdentifier=u.uldIdentifier;
            // Matrix.resize(length,vector<int> (width,0));
            vector<vector<int>> emptyArray(length,vector<int>(width,0));
            Matrix.build(length,width,emptyArray);
        }

        int getULDIdentifier(){
            return uldIdentifier;
        }

        // void print()
        // {
        //     cout<<"Matrix \n";
        //     for(int i=0;i<length;i++){
        //         for(int j=0;j<width;j++){
        //             // cout<<Matrix[i][j]<<" ";
        //             cout<<Matrix.max
        //         }
        //         cout<<'\n';
        //     }

        //     cout<<"\n";
        // }

        // Returns best position where Package can be inserted using Top Bottom Heuristic . Returns {-1,-1} if no such point is found 
        pair<tuple<int,int,int>,tuple<int,int,int>> findValidInsertionPoint(PACKAGE p){
            // print();
            // Weight check
            if(curWeight + p.weight > maxWeightLimit){
                return make_pair(make_tuple(-1,-1,-1),make_tuple(-1,-1,-1));
            }
            array<int,3> rotatedPackageDimensions = {p.length,p.width,p.height};

            tuple<int,int,int> bestStartPoint = make_tuple(-1,-1,-1);
            tuple<int,int,int> bestEndPoint = make_tuple(-1,-1,-1);
            double bestVolumeLossPerc = INF;
            for(int k=0;k<6;k++)
            {
                next_permutation(rotatedPackageDimensions.begin(),rotatedPackageDimensions.end());
                auto [packageLength,packageWidth,packageHeight] = rotatedPackageDimensions;
                int curPackageArea = packageLength*packageWidth;
                for(int x=0;x<=length-packageLength;x++){
                    for(int y=0;y<=width-packageWidth;y++){
                        // Checking insertion at base point (x,y)
                        int maximumHeight=0;
                        int curVolume=0;

                        // for(int i=x;i<x+packageLength;i++){
                        //     for(int j=y;j<y+packageWidth;j++){
                        //         maximumHeight=max(maximumHeight,Matrix[i][j]);
                        //         curVolume+=Matrix[i][j];
                        //     }
                        // }

                        maximumHeight = Matrix.maxQuery(x,y,x+packageLength-1,y+packageWidth-1);
                        curVolume = Matrix.sumQuery(x,y,x+packageLength-1,y+packageWidth-1);

                        // Height check
                        if(maximumHeight + packageHeight > height){
                            // Cannot fit inside ULD for current point
                            continue;
                        }

                        int volumeLoss = curPackageArea*maximumHeight - curVolume;
                        double volumeLossPerc = ((double)volumeLoss) / curPackageArea; 
                        if(volumeLossPerc < bestVolumeLossPerc){
                            bestStartPoint = {x,y,maximumHeight};
                            bestEndPoint = {x+packageLength,y+packageWidth,maximumHeight+packageHeight};
                            bestVolumeLossPerc = volumeLossPerc;
                        }
                    }
                }
            }

            // cout<<get<0>(bestStartPoint)<<" "<<Matrix.size()<<"\n";
            return make_pair(bestStartPoint,bestEndPoint);
        }

        void fitPackage(tuple<int,int,int> startPoint,tuple<int,int,int> endPoint,int packageWeight)
        {
            curWeight += packageWeight;

            auto currState = Matrix.getState();
            for(int i=get<0>(startPoint);i< get<0>(endPoint);i++){
                for(int j=get<1>(startPoint);j< get<1>(endPoint);j++){
                        // Matrix[i][j]=get<2>(endPoint);
                        currState[i][j] = get<2>(endPoint);
                }
            }
            Matrix.build(length,width,currState);
        }
};

long long delayCost(double a1,double b1)
{
    int k;
    vector<PACKAGE> packages;
    vector<ULD> ulds;

    parseInput(k, packages, ulds); // Parsing input

    OUTPUT output(packages.size());
    for(auto p:packages){
        output.outputRows[p.packageIdentifier] = OUTPUT_ROW(p.packageIdentifier);
    }

    packages.erase(packages.begin());
    ulds.erase(ulds.begin());
    vector<bool> containsPriority(ulds.size(),0);

    // Bottom Top Fill Heuristic

    // Sort ULDs

    function<double(int,int)> ULDCmp = [&](int volume,int weight){
        return volume/b1+weight;
    };

    sort(ulds.begin(),ulds.end(),[&](ULD u1,ULD u2){
        return ULDCmp(u1.length*u1.width*u1.height,u1.weightLimit) > ULDCmp(u2.length*u2.width*u2.height,u2.weightLimit);
    });

    // Sort Packages

    function<double(int,int)> priorityCmp = [&](int volume,int weight){
        // return volume/a1+weight;
        return -volume;
    };

    function<double(int,int,int)> economyCmp = [&](int volume,int weight,int cost){
        return (volume/a1+weight)/cost;
    };

    sort(packages.begin(),packages.end(),[&](PACKAGE p1,PACKAGE p2){
        if(p1.priority != p2.priority)
            return p1.priority > p2.priority;

        if(p1.priority){
            return priorityCmp(p1.length*p1.width*p1.height,p1.weight) < priorityCmp(p2.length*p2.width*p2.height,p2.weight);
        }
        else{
            return economyCmp(p1.length*p1.width*p1.height,p1.weight,p1.delayCost) < economyCmp(p2.length*p2.width*p2.height,p2.weight,p2.delayCost);
        }
    });

    // Iterate over Packages using Bottom Top Heuristic

    long long costOfDelay=0;
    vector<ULDBaseMatrix> v;
    for(auto u:ulds){
        v.push_back(ULDBaseMatrix(u));
    }

    for(auto p:packages){
        bool packageTaken = false;
        for(auto &matrix:v){
            pair<tuple<int,int,int>,tuple<int,int,int>> validInsertionPoint = matrix.findValidInsertionPoint(p);

            if(validInsertionPoint.first != make_tuple(-1,-1,-1)){
                packageTaken = true;
                
                // cout<<"Package "<<p.packageIdentifier<<" stored in ULD "<<matrix.getULDIdentifier()<<"\n";
                // cout<<"Start point : ";
                print2(validInsertionPoint.first,0);
                // cout<<"End point : ";
                print2(validInsertionPoint.second,0);

                if(p.priority)
                    containsPriority[matrix.getULDIdentifier()-1]=1;

                matrix.fitPackage(validInsertionPoint.first,validInsertionPoint.second,p.weight);

                output.outputRows[p.packageIdentifier].updateOutput(validInsertionPoint.first,validInsertionPoint.second,matrix.getULDIdentifier());
                break;
            }
        }

        if(packageTaken == false){
            costOfDelay += p.delayCost;
        }
    }

    // Generate Output

    for(int i=0;i<ulds.size();i++){
        if(containsPriority[i])
            costOfDelay+=k;
    }

    cout<<"Cost of Delay : "<<costOfDelay<<"\n";

    // Validate Output

    PACKAGE dummyPackage;
    ULD dummyULD;
    packages.insert(packages.begin(),dummyPackage);
    ulds.insert(ulds.begin(),dummyULD);
    validate(ulds, packages, output, k); // Validating output

    return costOfDelay;
}

int main()
{
    delayCost(ALPHA-500,BETA);

    return 0;
}

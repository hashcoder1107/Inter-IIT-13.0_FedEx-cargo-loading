// VECTOR<ULD>,VECTOR<PACKAGE> -> SOLUTION.CPP -> OUTPUT -> of class output.h

#include <bits/stdc++.h>
using namespace std;
#include "uld.h"
#include "package.h"
#include "output.h"
#include "parser.h"
#include "validator.h"


int main(){
    int k;
    vector<PACKAGE> packages;
    vector<ULD> ulds;

    parseInput(k,packages,ulds);

    OUTPUT sampleOutput(packages.size());

    for(int i=1;i<packages.size();i++){
        OUTPUT_ROW package(i);
        package.uldNumber=(i%2+1);
        if((i-1)/2){
            package.topRight={1000,1000,1000};
            package.bottomLeft={1000-packages[i].length,1000-packages[i].width,1000-packages[i].height};
        }
        else{
            package.bottomLeft={0,0,0};
            package.topRight={packages[i].length,packages[i].width,packages[i].height};
        }
        sampleOutput.outputRows[i]=package;
    }

    validate(ulds,packages,sampleOutput,k);
    return 0;
}
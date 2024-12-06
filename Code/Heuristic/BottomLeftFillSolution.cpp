#define INF 1e9
#define ALPHA 5587.836
#define BETA 5975.6536

#include "BottomLeftFillSolution.h"

using namespace std;

int main()
{
    int k;
    vector<PACKAGE> packages;
    vector<ULD> ulds;

    parseInput(k, packages, ulds);

    delayCost(ALPHA,BETA,k, packages, ulds);

    return 0;
}

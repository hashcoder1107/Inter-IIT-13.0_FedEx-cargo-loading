#define INF 1e9
#define ALPHA 7500
#define BETA 5975.6536

#include "BottomLeftFillSolution.h"

using namespace std;

int main()
{
    int k;
    vector<PACKAGE> packages;
    vector<ULD> ulds;

    parseInput(k, packages, ulds);

    int cost = delayCost(ALPHA,BETA,k, packages, ulds);
    cout << cost << endl;

    return 0;
}

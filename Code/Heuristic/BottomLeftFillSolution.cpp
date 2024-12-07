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

    string inputPath = "../../input/input.txt";

    parseInput(k, packages, ulds, inputPath);

    Solution solution;

    int cost = delayCost(ALPHA, BETA, k, packages, ulds, solution);

    if (solution.getValid() == true)
    {
        cout << solution.toString() << endl;
    }else {
        cout << "Invalid Solution: " << endl;
        cout << solution.toString() << endl;
    }

    return 0;
}

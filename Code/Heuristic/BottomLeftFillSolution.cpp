#include "Parameters/Parameters.h"

#include "BottomLeftFillSolution.h"

using namespace std;

bool validate(int k, vector<PACKAGE> &packages, vector<ULD> &ulds,
              Solution sol) {
  // Validate Output

  PACKAGE dummyPackage;
  ULD dummyULD;
  packages.insert(packages.begin(), dummyPackage);
  ulds.insert(ulds.begin(), dummyULD);
  auto chk = validate(ulds, packages, sol, k); // Validating output

  switch(chk) {
  case ValidationResult::SATISFIED:
    /* code */
    return true;
    break;
  case ValidationResult::OVERLAP:
    /* code */
    cout << "Validator: Two Packages Overlap with each other" << endl;
    break;
  case ValidationResult::VOLUME_OVERFLOW:
    /* code */
    cout << "Validator: A package overflows the assigned ULD's limit" << endl;
    break;
  case ValidationResult::WEIGHT_OVERFLOW:
    /* code */
    cout << "Validator: Total weight assigned to a ULD exceeds its capacity"
         << endl;
    break;

  default: break;
  }
  return false;
}

int main() {
  int k;
  vector<PACKAGE> packages;
  vector<ULD> ulds;

  string inputPath = INPUT_PATH;

  parseInput(k, packages, ulds, inputPath);

  Solution solution;

  int cost = delayCost(ALPHA, BETA, k, packages, ulds, solution);

  if(solution.getValid() == true) {
    cout << solution.toString() << endl;
  } else {
    cout << "Invalid Solution: " << endl;
    cout << solution.toString() << endl;
  }

  return 0;
}

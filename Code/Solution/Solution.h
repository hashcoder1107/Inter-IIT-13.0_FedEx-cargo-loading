#pragma once

#include <vector>
#include <string>
#include <set>
#include <map>

using namespace std;

struct AssignedPackage
{
  int packageId;
  int assignedUld;
  bool isPriority;
  int weight;
  tuple<int, int, int> bottomLeft;
  tuple<int, int, int> topRight;

  AssignedPackage()
  {
    AssignedPackage(-1, -1, -1, make_tuple(-1, -1, -1), make_tuple(-1, -1, -1), false);
  }

  AssignedPackage(int _packageId, int _assignedUld, int _weight, tuple<int, int, int> _bl, tuple<int, int, int> _tr, bool _isPriority)
  {
    weight = _weight;
    packageId = _packageId;
    assignedUld = _assignedUld;
    bottomLeft = _bl;
    topRight = _tr;
    isPriority = _isPriority;
  }
};

class Solution
{
  map<int, AssignedPackage> packages;
  int cost;
  bool valid;

public:
  Solution()
  {
    valid = true;
  }
  void setValid(bool flag)
  {
    valid = flag;
  }
  bool getValid()
  {
    return valid;
  }

  void createPackageAssignment(int packageId)
  {
    packages[packageId] = AssignedPackage(packageId, -1, -1, make_tuple(-1, -1, -1), make_tuple(-1, -1, -1), false);
  }

  void updatePackageAssignment(int packageId, int weight, tuple<int, int, int> bottomLeft, tuple<int, int, int> topRight, int uldId, bool isPriority)
  {
    packages[packageId] = AssignedPackage(packageId, uldId, weight, bottomLeft, topRight, isPriority);
  }

  void setCost(int _cost)
  {
    cost = _cost;
  }

  map<int, AssignedPackage> getPackages()
  {
    return packages;
  }

  string toString()
  {
    int cntAssigned = 0;
    set<int> priorityUlds;

    for (auto [_, package] : packages)
    {
      if (package.assignedUld != -1)
      {
        cntAssigned++;
        if (package.isPriority)
        {
          priorityUlds.insert(package.assignedUld);
        }
      }
    }

    string str = to_string(cost) + "," + to_string(cntAssigned) + "," + to_string(priorityUlds.size()) + "\n";

    for (auto [_, package] : packages)
    {
      if (package.packageId)
      {

        str += to_string(package.packageId) + ",";
        str += to_string(package.assignedUld) + ",";
        str += to_string(get<0>(package.bottomLeft)) + ",";
        str += to_string(get<1>(package.bottomLeft)) + ",";
        str += to_string(get<2>(package.bottomLeft)) + ",";
        str += to_string(get<0>(package.topRight)) + ",";
        str += to_string(get<1>(package.topRight)) + ",";
        str += to_string(get<2>(package.topRight)) + "\n";
      }
    }

    return str;
  }
};

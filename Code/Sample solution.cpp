#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Define a structure for the ULD (Unit Load Device)
struct ULD {
    int id;
    int length, width, height;
    int weight_limit;
    int current_weight;
    vector<vector<int>> packages; // Stores package IDs and their placement coordinates
};

// Define a structure for a Package
struct Package {
    int id;
    int length, width, height;
    int weight;
    bool is_priority;
};


bool checkPackageFit(ULD &uld, Package &pkg, int x, int y, int z) {

    if (x + pkg.length > uld.length || y + pkg.width > uld.width || z + pkg.height > uld.height)
        return false;

    // Check weight limit
    if (uld.current_weight + pkg.weight > uld.weight_limit)
        return false;

    // Check for overlap with already placed packages
    for (auto &placed_pkg : uld.packages) {
        int px = placed_pkg[1], py = placed_pkg[2], pz = placed_pkg[3];
        int pl = placed_pkg[4], pw = placed_pkg[5], ph = placed_pkg[6];

        if (!(x + pkg.length <= px || px + pl <= x ||
              y + pkg.width <= py || py + pw <= y ||
              z + pkg.height <= pz || pz + ph <= z)) {
            return false;
        }
    }

    // Check for stability
    if (z > 0) {
        bool supported = false;
        for (auto &placed_pkg : uld.packages) {
            int px = placed_pkg[1], py = placed_pkg[2], pz = placed_pkg[3];
            int pl = placed_pkg[4], pw = placed_pkg[5], ph = placed_pkg[6];

            if (z == pz + ph && x < px + pl && x + pkg.length > px &&
                y < py + pw && y + pkg.width > py) {
                supported = true;
                break;
            }
        }
        if (!supported)
            return false;
    }

    return true;
}


bool packPackage(ULD &uld, Package &pkg) {
    // Iterate through all possible positions in the ULD
    for (int x = 0; x <= uld.length - pkg.length; x++) {
        for (int y = 0; y <= uld.width - pkg.width; y++) {
            for (int z = 0; z <= uld.height - pkg.height; z++) {
                if (checkPackageFit(uld, pkg, x, y, z)) {
                    // Place the package in the ULD
                    uld.packages.push_back({pkg.id, x, y, z, pkg.length, pkg.width, pkg.height});
                    uld.current_weight += pkg.weight;
                    return true;
                }
            }
        }
    }
    return false; 
}

// Optimize the packing of packages into multiple ULDs
void optimizePacking(vector<ULD> &ulds, vector<Package> &packages) {
    // Sort packages by priority (priority packages first) and then by size (largest first)
    sort(packages.begin(), packages.end(), [](Package &a, Package &b) {
        if (a.is_priority != b.is_priority)
            return a.is_priority > b.is_priority;
        return (a.length * a.width * a.height) > (b.length * b.width * b.height);
    });

  
    for (auto &pkg : packages) {
        bool packed = false;
        for (auto &uld : ulds) {
            if (packPackage(uld, pkg)) {
                packed = true;
                break;
            }
        }
        if (!packed) {
            cout << "Package " << pkg.id << " could not be packed!" << endl;
        }
    }
}


int main() {
    // Input ULDs
    vector<ULD> ulds = {
        {1, 100, 80, 80, 250, 0, {}},
        {2, 100, 80, 80, 250, 0, {}}
    };

    // Input packages
    vector<Package> packages = {
        {1, 70, 40, 50, 100, true},
        {2, 70, 40, 50, 100, true},
        {3, 70, 40, 50, 150, false},
        {4, 70, 40, 50, 150, false}
    };

   
    optimizePacking(ulds, packages);

  
    cout << "Packing Results:" << endl;
    for (auto &uld : ulds) {
        cout << "ULD-" << uld.id << ": " << endl;
        for (auto &pkg : uld.packages) {
            cout << "  Package " << pkg[0] << " at (" << pkg[1] << ", " << pkg[2] << ", " << pkg[3]
                 << ") size (" << pkg[4] << "x" << pkg[5] << "x" << pkg[6] << ")" << endl;
        }
        cout << "  Remaining weight capacity: " << (uld.weight_limit - uld.current_weight) << endl;
    }

    return 0;
}

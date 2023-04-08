//Header file for the IC difusion model
#ifndef DIFUSIOLT_H
#define DIFUSIOLT_H

#include <vector>
using namespace std;

int simulate_LT(const vector<vector<int>>& G, vector<int>& S, double r, bool visualize = false);

#endif
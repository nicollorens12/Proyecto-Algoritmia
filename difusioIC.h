//Header file for the IC difusion model
#ifndef DIFUSIOIC_H
#define DIFUSIOIC_H

#include <vector>
using namespace std;

int simulate_IC(const vector<vector<int>>& G, vector<int>& S,  double p, bool visualize = true);

#endif
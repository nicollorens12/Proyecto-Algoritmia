#include <vector>
#include <iostream>

#include "difusioLT.h"

using namespace std;

int simulate_LT(const vector<vector<int>>& G, vector<int>& S, double r){
    // Initialize counter as number of active nodes
    int num_active_nodes = S.size();
    int n = G.size();
    vector<bool> active_nodes(n, false);

    for (int node : S) {
        active_nodes[node] = true;
    }
    vector<bool> updated_active_nodes = active_nodes;


    while(num_active_nodes < n) {
        //iterate over all nodes
        for(int i = 0; i<n; i++){
            if (active_nodes[i]) continue;
            // if node is inactive, check neighbors
            int num_neighbors = G[i].size();
            int num_active_neighbors = 0;

            // count number of active neighbors
            for (int neighbor : G[i]) {
                if (active_nodes[neighbor]) num_active_neighbors++;
            }
            //check if threshold is met, i.e. if enough neighbors are active
            if (num_active_neighbors >= r * num_neighbors) {
                updated_active_nodes[i] = true;
            }
        }

        // check if any nodes were activated, and update active nodes
        if (active_nodes == updated_active_nodes) break;
        active_nodes = updated_active_nodes;
    }

    return num_active_nodes;
}




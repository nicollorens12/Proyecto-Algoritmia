/*
#include <vector>
#include <iostream>

#include "difusioLT.h"
#include "graph.h"

using namespace std;

int simulate_LT(const vector<vector<int>>& G,const vector<int>& S, double r) {
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
            // if node is inactive and has no neighbors, skip it
            if (G[i].empty()) continue;
            // if node is inactive and has neighbors, check neighbors
            int num_neighbors = G[i].size();
            int num_active_neighbors = 0;

            // count number of active neighbors
            for (int neighbor : G[i]) {
                if (active_nodes[neighbor]) num_active_neighbors++;
            }
            //check if threshold is met, i.e. if enough neighbors are active
            if (num_active_neighbors >= r * num_neighbors) {
                updated_active_nodes[i] = true;
                num_active_nodes++;
            }
        }

        // check if any nodes were activated, and update active nodes
        if (active_nodes == updated_active_nodes) break;
        active_nodes = updated_active_nodes;
    }

    return num_active_nodes;
}

*/
#include <vector>
#include <iostream>

#include "difusioLT.h"
#include "graph.h"

using namespace std;

int simulate_LT(const vector<vector<int>>& G, const vector<int>& S, double r) {
    // Initialize counter as the number of active nodes
    int num_active_nodes = S.size();
    int n = G.size();
    vector<int> active_nodes(n, 0);

    for (int node : S) {
        if(0<node && node<n){ active_nodes[node] = 1;}
    }
    vector<int> updated_active_nodes = active_nodes;

    while (num_active_nodes < n) {
        // Iterate over all nodes
        for (int i = 0; i < n; i++) {
            if (active_nodes[i]) continue;
            // If the node is inactive and has no neighbors, skip it
            if (G[i].empty()) continue;
            // If the node is inactive and has neighbors, check neighbors
            int num_neighbors = G[i].size();
            int num_active_neighbors = 0;

            // Count the number of active neighbors
            for (int neighbor : G[i]) {
                if (active_nodes[neighbor]) num_active_neighbors++;
            }
            // Check if the threshold is met, i.e., if enough neighbors are active
            if (num_active_neighbors >= r * num_neighbors) {
                updated_active_nodes[i] = 1;
                num_active_nodes++;
            }
        }

        // Check if any nodes were activated and update active nodes
        if (active_nodes == updated_active_nodes) break;
        active_nodes = updated_active_nodes;
    }

    return num_active_nodes;
}



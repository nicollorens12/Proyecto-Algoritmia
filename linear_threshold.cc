/*
I wrote this method with the given simplifications in mind. It does not account for edge weights
or different threshold functions.
*/
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

// Parameters: undirected graph G = (V,E), ratio r in [0, 1], and initial set S of activated nodes
// Output: final number of activated nodes using diffusion by linear threshold
int simulate_LT(vector<vector<int>>& G, double r, vector<int>& S) {
    // Initialize counter as number of active nodes
    int counter = S.size();
    int V = G.size();
    vector<bool> active(V, false);
    
    for (int node : S) {
        active[node] = true;
    }
    
    // 2 conditions to end loop. Either:
    // all nodes are activated
    // no new nodes have been activated since the last pass
    while (counter < V) {
        // store number of active nodes:
        int initial = counter;

        for (int i=0; i<V; i++) {
            // for all inactive nodes, check neighbor influence:
            if (!active[i]) {
                // threshold = r * degree
                double threshold = r * G[i].size();

                // add influence of each active neighbor:
                int influence = 0;
                for (int neighbor : G[i]) { 
                    if(active[neighbor]) {
                        influence++;
                    }
                    // if influence surpasses threshold, 
                    if(influence >= threshold) {
                        active[i] = true;
                        counter++;
                        break;
                    }
                }
            }
        }
        // check to see if there were new activations:
        if (counter == initial) {
            break;
        }
    }

    return counter;
}


int main() {
    vector<vector<int>> G = { {1}, {0, 2}, {1, 3}, {2, 4, 5}, {3, 6}, {3, 7}, {4, 8}, {5, 9}, {6}, {7} };
    double r = 0.5;
    vector<int> S = {0, 7, 8};
    
    int C = simulate_LT(G, r, S);
    
    cout << "The number of nodes activated using LT with a resistance ratio r = " << r << " is: " << C << endl;
    
}
#include <vector>
#include <iostream>

using namespace std;

int procedure(vector<vector<int>> G, vector<int> S, double r){
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

int main(){
    vector<vector<int> > G = { {1}, {0, 2}, {1, 3}, {2, 4, 5}, {3, 6}, {3, 7}, {4, 8}, {5, 9}, {6}, {7} };
    double r = 0.6;

    vector<int> S = {0, 7, 8};

    cout << "With an LT procedure there are " << procedure(G,S,r) << " node(s) active(s) with a R of " << r << " and a intial set of " << S.size() << " elements" << endl;

}

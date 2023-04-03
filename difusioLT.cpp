#include <vector>
#include <iostream>

using namespace std;

int procedure(vector<vector<int>> G, vector<int> S, double r){
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



int main(int argc, char** argv){
    vector<vector<int> > G = { 
        {1}, {0, 2}, {1, 3}, {2, 4, 5}, {3, 6}, 
        {3, 7}, {4, 8}, {5, 9}, {6}, {7} 
    };
    vector<int> S = {0, 7, 8};
    double r = 0.6;

    //check if different argument for r is provided
    if (argc > 1) {
        r = atof(argv[1]);
    }


    cout << "With an LT procedure there are " << procedure(G,S,r) 
        << " node(s) active(s) with a R of " << r << " and a intial set of " 
        << S.size() << " elements" << endl;

}

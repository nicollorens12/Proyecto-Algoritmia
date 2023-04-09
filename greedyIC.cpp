#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>

#include "difusioIC.h"
#include "readData.h"
#include "graph.h"

using namespace std;

// CELF based greedy

vector<int> greedy_IC(const vector<vector<int>>& G, double p){
    int graph_size = G.size();
    vector<int> S;
    // Nodes sorted by their marginal gain
    priority_queue<pair<double, int>> Q;
    // Compute the marginal gain for each node
    for (int i = 0; i < graph_size; ++i) {
        double marginal_gain = simulate_IC(G, {i}, p);
        Q.push(make_pair(marginal_gain, i));
    }
    vector<int> last_update(graph_size, 0);
    int influence = 0;
    // Select the node with the highest marginal gain and add it to the set S
    while (influence < graph_size) {
        int node = Q.top().second;
        int set_size = S.size();
        Q.pop();
        if (last_update[node] == set_size) {
            S.push_back(node);
            influence += Q.top().first;
        } else {
            double marginal_gain = simulate_IC(G, S, p) - influence;
            last_update[node] = set_size;
            Q.push(make_pair(marginal_gain, node));
        }
    }
    return S;
}

int main(int argc, char **argv) {
    vector<vector<int> > G = read_Data(argc, argv);
    double p = 0.5;
    vector<int> result = greedy_IC(G,p);

    cout << "-------------IC GREEDY-------------" << endl;
    cout << "MINIMUM INITIAL NODES: {";
    int result_size = result.size();
    for(int k = 0; k < result_size; ++k) {
        if(k == result_size - 1) cout << result[k];
        else cout << result[k] << ", ";
    }
    
    cout << "}" << endl;
    cout << "With a probability p of: " << p << endl;
    cout << "SIZE: " << result_size << endl;
    
}

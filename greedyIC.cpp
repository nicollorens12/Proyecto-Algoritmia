#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <chrono>

#include "difusioIC.h"
#include "readData.h"
#include "graph.h"

using namespace std;

bool compareMarginalGain(const int& u, const int& v, const vector<vector<int>>& G, double p) {
    return simulate_IC(G, {u}, p) < simulate_IC(G, {v}, p);
}

vector<int> greedy_IC(const vector<vector<int>>& G, double p){
  int graph_size = G.size();
  set<int> S;
  vector<int> node_order(graph_size);
  for (int i = 0; i < graph_size; ++i) {
      node_order[i] = i;
  }
  // Sort nodes by their marginal gain
  sort(node_order.begin(), node_order.end(), [&](int u, int v) {
    return compareMarginalGain(u, v, G, p);
  });
  int influence = 0;
  // Select the node with the highest marginal gain and add it to the set S
  for (int i = graph_size - 1; i >= 0; --i) {
      int node = node_order[i];
      int marginal_gain = simulate_IC(G, {node}, p) - influence;
      if (marginal_gain > 0) {
          S.insert(node);
          influence += marginal_gain;
      }
  }
  return vector<int>(S.begin(), S.end());
}


int main(int argc, char **argv) {
    vector<vector<int> > G = read_Data(argc, argv);
    double p = 0.7;
    
    auto start = std::chrono::high_resolution_clock::now();
    vector<int> result = greedy_IC(G,p);
    
    auto end = std::chrono::high_resolution_clock::now();
  
    auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  
    cout << "Execution time: " << elapsed_time.count() << " ms" << std::endl;

    cout << "-------------IC GREEDY-------------" << endl;
    cout << "MINIMUM INITIAL NODES: {";
    int result_size = result.size();
    for(int k = 0; k < result_size; ++k) {
        if(k == result_size - 1) cout << result[k]+1;
        else cout << result[k]+1 << ", ";
    }
    
    cout << "}" << endl;
    cout << "With a probability p of: " << p << endl;
    cout << "SIZE: " << result_size << endl;
    
}

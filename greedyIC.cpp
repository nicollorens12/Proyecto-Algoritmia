#include <vector>
#include <iostream>
#include <algorithm>

#include "difusioIC.h"
#include "readData.h"
#include "graph.h"

using namespace std;

struct node_info{
    int node;
    int degree;
};

bool node_comparator(node_info n1, node_info n2){
    return n1.degree < n2.degree;
}

vector<int> greedy_IC(const vector<vector<int>>& G, double p){

    int V = G.size();
    vector<int> S = vector<int> (V);
    for(int i = 0; i < V; ++i) S[i] = i;
    vector<node_info> degree(V);

    for(int i = 0; i < V; ++i) {
        degree[i].node = i;
        degree[i].degree = G[i].size();
    }
    sort(degree.begin(),degree.end(), node_comparator);
    bool stop = false;
    int e_degree = 0;
    vector<int> old_S;
    while(!stop){

        vector<int> aux;
        for(int j = e_degree; j < V; ++j) aux.push_back(degree[j].node);

        //si aux es vacio ni intentar
        old_S = S;
        S = aux;
        int procedure_res = simulate_IC(G,S,p);
        if(procedure_res != V) stop = true;
        else ++e_degree;

    }
    cout << "-------------IC GREEDY-------------" << endl;
    cout << "MINIMUM INITIAL NODES: {";
    int old_S_size = old_S.size();
    for(int k = 0; k < old_S_size; ++k) {
        if(k == old_S_size - 1) cout << old_S[k];
        else cout << old_S[k] << ", ";
    }
    
    //visualizeGraph(G, old_S, "best_solution.dot");
    
    cout << "}" << endl;
    cout << "With a probability p of: " << p << endl;
    cout << "SIZE: " << old_S_size << endl;
    
    return old_S;
    
}

int main(int argc, char **argv) {
    vector<vector<int> > G = read_Data(argc, argv);
    double p = 0.5;
    //greedy_IC(G,p);
}

#include <vector>
#include <iostream>
#include <algorithm>

#include "readData.h"
#include "difusioLT.h"

using namespace std;

struct node_info{
    int node;
    int degree;
};

bool node_comparatorLT(node_info n1, node_info n2){
    return n1.degree < n2.degree;
}

vector<int> greedy_LT(const vector<vector<int> >& G, double r){

    int V = G.size();
    vector<int> S = vector<int> (V);
    for(int i = 0; i < V; ++i) S[i] = i;
    vector<node_info> degree(V);

    for(int i = 0; i < V; ++i) {
        degree[i].node = i;
        degree[i].degree = G[i].size();
    }
    sort(degree.begin(),degree.end(), node_comparatorLT);
    bool stop = false;
    int e_degree = 0;
    vector<int> old_S;
    while(!stop){

        vector<int> aux;
        for(int j = e_degree; j < V; ++j) aux.push_back(degree[j].node);

        //si aux es vacio ni intentar
        old_S = S;
        S = aux;
        int procedure_res = simulate_LT(G,S,r);
        if(procedure_res != V) stop = true;
        else ++e_degree;

    }
    return old_S;
}

/*
int main(int argc, char **argv){
    vector<vector<int> > G = read_Data(argc, argv);
    double r = 0.6;
    vector<int> result = greedy_LT(G,r);

    cout << "-------------LT GREEDY-------------" << endl;
    cout << "MINIMUM INITIAL NODES: {";
    int result_size = result.size();
    for(int k = 0; k < result_size; ++k) {
        if(k == result_size - 1) cout << result[k];
        else cout << result[k] << ", ";
    }
    cout << "}" << endl;
    cout << "With an R of: " << r << endl;
        
    cout << "SIZE " << result_size << endl; 
    
}

*/
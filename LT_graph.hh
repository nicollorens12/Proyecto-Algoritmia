#ifndef LT_GRAPH_HH
#define LT_GRAPH_HH

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct node_info{
    int node;
    int degree;
};

class LTGraph{

    private:
        vector<vector<int>> G;
        double r;
        vector<int> S;
    public:

    LTGraph(vector<vector<int> > graph, vector<int> S_a, float r_a){
        G = graph;
        r = r_a;
        S = S_a;
    }

    LTGraph(vector<vector<int> > graph, float r_a){
        G = graph;
        r = r_a;
        int V = G.size();
        S = vector<int> (V);
        for(int i = 0; i < V; ++i) S[i] = i;
    }

    int procedure(){
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
    static bool node_comparator(node_info n1, node_info n2){
        return n1.degree < n2.degree;
    }

    void greedy(){
        int V = G.size();
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
            for(int j = e_degree; j < V; ++j) {

                aux.push_back(degree[j].node);

                //cout << "SIZE DE AUX ES: " << aux.size() << endl;
            }
            //si aux es vacio ni intentar
            old_S = S;
            S = aux;
            int procedure_res = procedure();
            //cout << "CON AUX SIZE DE: " << aux.size() <<
            if(procedure_res != V) stop = true;
            else ++e_degree;

        }
        cout << "MINIMUM INITIAL NODES: {";
        int old_S_size = old_S.size();
        for(int k = 0; k < old_S_size; ++k) {
            if(k == old_S_size - 1) cout << old_S[k];
            else cout << old_S[k] << ", ";
        }
        cout << "}" << endl;
    }


};

#endif


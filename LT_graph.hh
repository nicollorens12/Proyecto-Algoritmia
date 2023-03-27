#ifndef LT_GRAPH_HH
#define LT_GRAPH_HH

#include <vector>
#include <iostream>
using namespace std;

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

};

#endif


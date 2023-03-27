#ifndef IC_GRAPH_HH
#define IC_GRAPH_HH

#include <vector>
#include <iostream>
#include <queue>
#include <cstdlib>

using namespace std;

class ICGraph{

    private:
        vector<vector<int>> G;
        double p;
        vector<int> S;
    public:

    ICGraph(vector<vector<int> > graph, vector<int> S_a, double p_a){
        G = graph;
        p = p_a;
        S = S_a;
    }

    int procedure(){
        // We initialize the counter as the number of active nodes
        int counter = S.size();
        int vector_size = G.size();
        vector<bool> active(vector_size, false);
        queue<int> Q;
        // First we mark the nodes that have been activated using an additional structure, a vector of booleans called active, and we put in a queue the vectors that are active.
        for (int node : S) {
            active[node] = true;
            Q.push(node);
        }
        // Until the queue is empty, an attempt is made to activate each neighbor of the nodes present in the queue. This process is performed only once; thus, if activation of a node v1 fails, no further attempts will be made to activate that node.
        while (!Q.empty()) {
            int node = Q.front();
            Q.pop();
            for (int neighbour : G[node]) {
                double random_number = (double) rand() / RAND_MAX;
                // Here because IC is a stochastic model, we  generate a random number between [0,1] and we compare it to the value of p to determine if the node can be activated.
                if (!active[neighbour] && (p > random_number)) {
                    active[neighbour] = true;
                    Q.push(neighbour);
                    ++counter;
                }
            }
        }
        return counter;
    }

};

#endif


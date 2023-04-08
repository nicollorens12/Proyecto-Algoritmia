#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include "difusioIC.h"
#include "graph.h"

using namespace std;

/*  Graphs are represented as a vector of vectors of integers, 
    where each vector of integers represents a node and the elements
    of the vector are the neighbors of the node.

    Graphs in the IC model are undirected, so if there is an edge between 
    node u and node v, then v is a neighbor of u and u is a neighbor of v. */

// Prerequisites: a undirected graph G, a real number p between [0,1] and a subset, S, of the set of vertices of G
// Post: the number of vertices that have been influenced(activated)
int simulate_IC(const vector<vector<int>>& G,  vector<int>& S, double p) {
    // We initialize the counter as the number of active nodes
	int counter = S.size();
	int vector_size = G.size();
    vector<bool> active_nodes(vector_size, false);
    queue<int> Q;



  /* First we mark the nodes that have been activated using an additional structure, 
  a vector of booleans called active, and we put in a queue the vectors that are active.*/
    for (int node : S) {
      active_nodes[node] = true;
      Q.push(node);
     }

    /* Until the queue is empty, an attempt is made to activate each neighbor of the nodes 
    present in the queue. This process is performed only once; thus, if activation of a 
    node v1 fails, no further attempts will be made to activate that node.*/
    while (!Q.empty()) {
        int node = Q.front();
        Q.pop();
        for (int neighbour : G[node]) {
      		double random_number = (double) rand() / RAND_MAX;
      		/* Here because IC is a stochastic model, we  generate a random number between [0,1] 
            and we compare it to the value of p to determine if the node can be activated.*/
            if (!active_nodes[neighbour] && (p > random_number)) {
                active_nodes[neighbour] = true;
                Q.push(neighbour);
                ++counter;
            }
        }
    }
    return counter;
}
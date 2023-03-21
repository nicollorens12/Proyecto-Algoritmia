/*
I am uncertain about the stochastic component of the model. Specifically, I am unsure if each neighboring node has a unique random probability of being 
activated or if all nodes share the same random probability. I men if the random value is 0.7 then we need to compare it with p and generate another 
random value for each neighbour, or for that graph G the random value of 0.7 it will be the same for all the neighbours.I assume that the former is 
true and that the random value to compare it with p varies for each neighboring node. Additionally, I am uncertain if the graph must be connected 
for the model to function properly. I understand that even if the graph is not connected, the model will still operate in the same manner.
*/


#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>

using namespace std;

// Prerequisites: a undirected graph G, a real number p between [0,1] and a subset, S, of the set of vertices of G
// Post: the number of vertices that have been influenced(activated)
int simulate_IC(vector<vector<int>>& G, double p, vector<int>& S) {
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


int main() {
  vector<vector<int>> G = { {1}, {0, 2}, {1, 3}, {2, 4, 5}, {3, 6}, {3, 7}, {4, 8}, {5, 9}, {6}, {7} };
  double p = 0.8;
  vector<int> S = {0, 7, 8};
  
  int counter = simulate_IC(G, p, S);
  
  cout << "The number of nodes activated using IC with a probability p = " << p << " is: " << counter << endl;
  
}

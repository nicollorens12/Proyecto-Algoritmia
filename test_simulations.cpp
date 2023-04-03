#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include "difusioIC.h"
#include "difusioLT.h"

using namespace std;


vector<vector<int>> generate_graph(int num_nodes, int num_edges) {
    vector<vector<int>> graph(num_nodes);

    for (int i = 0; i < num_edges; ++i) {
        int u = rand() % num_nodes;
        int v = rand() % num_nodes;

        // Add edge between nodes u and v
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    return graph;
}


int main(int argc, char* argv[]) {
    srand(time(0));

    // Default values
    int choice = 1;
    double p_or_r = 0.5;

    // If no argument is passed, print usage instructions and exit
    if (argc == 1) {
        cout << "Usage: " << argv[0] << " [1|2] [p|r]" << endl;
        cout << "     1 (default): Test difusioIC with p as the probability of influence" << endl;
        cout << "     2: Test difusioLT with r as the threshold ratio" << endl;
        cout << "     p|r: Optional value for p or r (default: 0.5)" << endl;
        return 0;
    }

    // Read command-line arguments
    if (argc > 1) {
        choice = atoi(argv[1]);
    }
    if (argc > 2) {
        p_or_r = atof(argv[2]);
    }

    // Generate a sample graph
    int num_nodes = 10;
    int num_edges = 15;
    vector<vector<int>> G = generate_graph(num_nodes, num_edges);

    // Generate an initial set of active nodes
    vector<int> S = {0, 1};

    // Run the chosen simulation
    int num_activated_nodes;
    if (choice == 1) {
        cout << "Testing difusioIC with p = " << p_or_r << endl;
        num_activated_nodes = simulate_IC(G, S, p_or_r);
    } else {
        cout << "Testing difusioLT with r = " << p_or_r << endl;
        num_activated_nodes = simulate_LT(G, S, p_or_r);
    }

    cout << "Number of activated nodes: " << num_activated_nodes << endl;

    return 0;
}

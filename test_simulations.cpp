#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <set>
#include <random>
#include <filesystem>

#include "difusioIC.h"
#include "difusioLT.h"
#include "graph.h"

using namespace std;



int main(int argc, char* argv[]) {
    srand(time(0));

    // Default values
    int choice = 1;
    double p_or_r = 0.5;
    int num_nodes = 10;
    int num_edges = 15;
    int size_subset = 2;

    // If no argument is passed, print usage instructions and exit
    if (argc == 1) {
        cout << endl <<"Usage: " << endl<< argv[0] << " [1|2] [p|r] [num_nodes] [num_edges] [size_subset]" << endl;
        cout <<endl<< "     1 (default): Test difusioIC with p as the probability of influence" << endl;
        cout << "     2: Test difusioLT with r as the threshold ratio" << endl;
        cout << "     p|r: Optional value for p or r (default: 0.5)" << endl;
        cout << "     num_nodes: Optional value for number of nodes (default: 10)" << endl;
        cout << "     num_edges: Optional value for number of edges (default: 15)" << endl; 
        cout << "     size_subset: Optional value for size of subset (default: 2)" << endl <<endl;
        return 0;
    }

    // Read command-line arguments
    // adapt below to include arg for num_nodes and num_edges

    if (argc > 1) {
        choice = atoi(argv[1]);
    }
    if (argc > 2) {
        p_or_r = atof(argv[2]);
    }
    if (argc > 3) {
        num_nodes = atoi(argv[3]);
    }
    if (argc > 4) {
        num_edges = atoi(argv[4]);
    }
    if (argc > 5) {
        size_subset = atoi(argv[5]);
    }


    // Generate a sample graph
    vector<vector<int>> G = generate_graph(num_nodes, num_edges);
    
    // Generate an initial subset of size size_subset of randomly active nodes (not two times the same node)
    vector<int> S;
    set<int> added_nodes;
    while (S.size() < static_cast<size_t>(size_subset)) {
        int node = rand() % num_nodes;
        if (added_nodes.find(node) == added_nodes.end()) {
            S.push_back(node);
            added_nodes.insert(node);
        }
    }

    //clear debug output"
    system("rm -rf debug_output/*");

    //visualize initial state
    visualizeGraph(G, S, "initial_state");
    cout << endl <<  "      Initial Graph visualization saved in debug_output/initial_state.png" << endl<<endl;

    // Run the chosen simulation
    int num_activated_nodes;
    if (choice == 1) {
        cout << "   - Testing difusioIC with p = " << p_or_r << endl;
        num_activated_nodes = simulate_IC(G, S, p_or_r);
    } else {
        cout << "    - Testing difusioLT with r = " << p_or_r << endl;
        num_activated_nodes = simulate_LT(G, S, p_or_r);
    }
  
    cout << "    - Number of activated nodes after simulation: " << num_activated_nodes << endl << endl;


    return 0;
}
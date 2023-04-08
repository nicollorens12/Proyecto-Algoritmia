#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <set>
#include <random>
#include <filesystem>
#include "difusioIC.h"
#include "difusioLT.h"
#include "graph_visualizer.h"
#include "metaheuristicLT.h"

using namespace std;


vector<vector<int>> generate_graph(int num_nodes, int num_edges) {
    if (num_edges > (num_nodes * (num_nodes - 1)) / 2) {
        throw runtime_error("Invalid input: too many edges for the given number of nodes.");
    }
    
    vector<vector<int>> graph(num_nodes);
    set<pair<int, int>> added_edges;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> node_dist(0, num_nodes - 1);

    while (added_edges.size() < static_cast<size_t>(num_edges)) {
        int node1 = node_dist(gen);
        int node2 = node_dist(gen);

        if (node1 != node2 && added_edges.find(make_pair(node1, node2)) == added_edges.end() &&
            added_edges.find(make_pair(node2, node1)) == added_edges.end()) {
            graph[node1].push_back(node2);
            graph[node2].push_back(node1);
            added_edges.insert(make_pair(node1, node2));
        }
    }

    return graph;
}



int main(int argc, char* argv[]) {
    srand(time(0));

    // Default values
    int algo_choice = 2;
    int num_nodes = 10;
    int num_edges = 15;
    int size_subset = 2;
    int maxGenerations = 100;
    int populationSize = 100;
    double mutationProbability = 0.05;
    int tournamentSize = 5;
    int k = 3;
    int maxGenerations = 100;
    double p_or_r = 0.5;

    //create the same instructions but for the variables above (Default values)
    if (argc == 1) {
        cout << endl <<"Usage: " << endl<< argv[0] << " [1|2] [p|r] [num_nodes] [num_edges] [size_subset] [max_generations] [mutationProbability] [tournamentSize] [k] [maxGenerations]" << endl;
        cout <<endl<< "     1 (default): Test metaheuristicIC" << endl;
        cout << "     2: Test metaheuristicLT" << endl;
        cout << "     p|r: Optional value for p or r (default: 0.5)" << endl;
        cout << "     num_nodes: Optional value for number of nodes (default: 10)" << endl;
        cout << "     num_edges: Optional value for number of edges (default: 15)" << endl;
        cout << "     size_subset: Optional value for size of subset (default: 2)" << endl;
        cout << "     max_generations: Optional value for max generations (default: 100)" << endl;
        cout << "     mutationProbability: Optional value for mutation probability (default: 0.05)" << endl;
        cout << "     tournamentSize: Optional value for tournament size (default: 5)" << endl;
        cout << "     k: Optional value for k (default: 3)" << endl;
        cout << "     maxGenerations: Optional value for max generations (default: 100)" << endl <<endl;
        return 0;
    }

    // Read command-line arguments
    // adapt below to include arg for num_nodes and num_edges

    if (argc > 1) {
        algo_choice = atoi(argv[1]);
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
    if (argc > 6) {
        max_generations = atoi(argv[6]);
    }
    if (argc > 7) {
        mutationProbability = atof(argv[7]);
    }
    if (argc > 8) {
        tournamentSize = atoi(argv[8]);
    }
    if (argc > 9) {
        k = atoi(argv[9]);
    }
    if (argc > 10) {
        maxGenerations = atoi(argv[10]);
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

    //visualize initial graph
    //outputGraphToDotFile(G, S, "debug_output/initial_graph.dot");

    // Run the chosen simulation
    int num_activated_nodes;
    if (algo_choice == 1) {
        cout << "Testing difusioIC with p = " << p_or_r << endl;
        num_activated_nodes = simulate_IC(G, S, p_or_r, true);
    } else {
        cout << "Testing metaheuristicLT with the following paremters: " << endl;
        cout << "     max_generations: " << maxGenerations << endl;
        cout << "     mutationProbability: " << mutationProbability << endl;
        cout << "     tournamentSize: " << tournamentSize << endl;
        cout << "     k: " << k << endl;
        cout << "     maxGenerations: " << maxGenerations << endl;
        num_activated_nodes = metaheuristicLT(G, S, k,  maxGenerations, populationSize, mutationProbability, tournamentSize, p_or_r);
    }
  
    cout << "Number of activated nodes after simulation: " << num_activated_nodes << endl;
    
    cout << endl << "Initial active nodes:";
    for (const int& node : S) {
        cout << node << " ";
    }
    //cout << endl << "Check the visualization in debug_output" << endl;


    return 0;
}
#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <set>
#include <random>
#include <filesystem>

#include "metaheuristicLT.h"
#include "metaheuristicIC.h"
#include "graph.h"
#include "difusioLT.h"
#include "difusioIC.h"


using namespace std;



int main(int argc, char* argv[]) {
    srand(time(0));

    // Default values
    int algo_choice = 2;
    int num_nodes = 10;
    int num_edges = 15;
    int k = 3;
    int maxGenerations = 100;
    int populationSize = 100;
    double mutationProbability = 0.05;
    int tournamentSize = 5;
    double p_or_r = 0.5;

    //create the same instructions but for the variables above (Default values)
    if (argc == 1) {
        cout << endl <<"Usage: " << endl<< argv[0] << " [1|2] [p|r] [num_nodes] [num_edges] [k] [max_generations] [mutationProbability] [tournamentSize] [maxGenerations]" << endl;
        cout <<endl<< "     1 (default): Test metaheuristicIC" << endl;
        cout << "     2: Test metaheuristicLT" << endl;
        cout << "     p|r: Optional value for p or r (default: 0.5)" << endl;
        cout << "     num_nodes: Optional value for number of nodes (default: 10)" << endl;
        cout << "     num_edges: Optional value for number of edges (default: 15)" << endl;
        cout << "     k: Optional value for size of subset (default: 2)" << endl;
        cout << "     max_generations: Optional value for max generations (default: 100)" << endl;
        cout << "     mutationProbability: Optional value for mutation probability (default: 0.05)" << endl;
        cout << "     tournamentSize: Optional value for tournament size (default: 5)" << endl;
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
        k = atoi(argv[5]);
    }
    if (argc > 6) {
        maxGenerations = atoi(argv[6]);
    }
    if (argc > 7) {
        mutationProbability = atof(argv[7]);
    }
    if (argc > 8) {
        tournamentSize = atoi(argv[8]);
    }
    if (argc > 9) {
        maxGenerations = atoi(argv[10]);
    }



    // Generate a sample graph
    vector<vector<int>> G = generate_graph(num_nodes, num_edges);

    // Generate an initial subset of size k of randomly active nodes (not two times the same node)
    vector<int> S;
    set<int> added_nodes;
    while (S.size() < static_cast<size_t>(k)) {
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
    vector<int> best_solution;

    if (algo_choice == 1) {
       cout << "Testing metaheuristicLT with the following paremters: " << endl;
        cout << "     max_generations: " << maxGenerations << endl;
        cout << "     mutationProbability: " << mutationProbability << endl;
        cout << "     tournamentSize: " << tournamentSize << endl;
        cout << "     k: " << k << endl;
        cout << "     maxGenerations: " << maxGenerations << endl;
        cout << "     p_or_r: " << p_or_r << endl;
        best_solution = metaheuristicLT(G, S, p_or_r, k,  maxGenerations, populationSize, mutationProbability, tournamentSize);
        visualizeGraph(G, best_solution, "best_solution.dot");
        cout << "See the best solution for the Graph G and S of size k = " << k << " in debug_output/best_solution.dot.png" << endl;

    } else {
        cout << "Testing metaheuristicLT with the following paremters: " << endl;
        cout << "     max_generations: " << maxGenerations << endl;
        cout << "     mutationProbability: " << mutationProbability << endl;
        cout << "     tournamentSize: " << tournamentSize << endl;
        cout << "     k: " << k << endl;
        cout << "     maxGenerations: " << maxGenerations << endl;
        cout << "     p_or_r: " << p_or_r << endl;

        best_solution = metaheuristicLT(G, S, p_or_r, k,  maxGenerations, populationSize, mutationProbability, tournamentSize);
        visualizeGraph(G, best_solution, "best_solution.dot");

        cout << "See the best solution for the Graph G and S of size k = " << k << " in debug_output/best_solution.dot.png" << endl;
    }

    //cout << endl << "Check the visualization in debug_output" << endl;


    return 0;
}
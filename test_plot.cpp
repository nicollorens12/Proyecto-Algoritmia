#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <fstream>
#include "graph.h"
#include "metaheuristicLT.h"

using namespace std;

int main() {
    // List of graph sizes to test
    //vector<int> graph_sizes = {10, 50, 100, 250, 500, 750, 1000, 2500, 5000, 7500, 10000};
    vector<int> graph_sizes = {20000, 30000, 50000, 100000};

    // Number of random graphs to generate for each size
    int num_graphs_per_size = 10;

    // Number of edges per graph
    int num_edges_per_graph = 2;

    // Open the output file to save the results
    ofstream results_file("metaheuristicLT_results.csv");
    results_file << "GraphSize,AverageExecutionTime" << endl;

    // Loop over each graph size
    for (int graph_size : graph_sizes) {
        double total_execution_time = 0.0;

        // Loop over each random graph for this size
        for (int i = 0; i < num_graphs_per_size; i++) {
            // Generate a random graph of the specified size and number of edges
            vector<vector<int>> graph = generate_graph(graph_size, num_edges_per_graph * graph_size);

            // Run metaheuristicLT and measure the execution time
            auto start_time = chrono::high_resolution_clock::now();
            vector<int> seed_set = metaheuristicLT(graph, 0.5);
            auto end_time = chrono::high_resolution_clock::now();
            chrono::duration<double> execution_time = end_time - start_time;

            // Record the execution time for this graph
            total_execution_time += execution_time.count();
        }

        // Calculate the average execution time for this graph size
        double average_execution_time = total_execution_time / num_graphs_per_size;

        // Write the results to the output file
        results_file << graph_size << "," << average_execution_time << endl;
    }

    // Close the output file
    results_file.close();

    return 0;
}

#include <string>
#include <iostream>
#include <chrono>
#include <fstream>
#include "difusioLT.h"
#include "difusioIC.h"
#include "graph.h"
#include "greedyIC.h"
#include "greedyLT.h"
#include "localSearchLT.h"
#include "localSearchIC.h"
#include "metaheuristicLT.h"
#include "metaheuristicIC.h"
#include "readData.h"

using namespace std;
int main(int argc, char* argv[]) {
    // List the first ten dimacs graph filenames
    vector<string> filenames = {
        "graph_dolphins.dimacs", "graph_karate.dimacs", "graph_football.dimacs",
        "graph_jazz.dimacs", "socfb-nips-ego.dimacs", "socfb-Mich67.dimacs"//,
        //"socfb-Brandeis99.dimacs", "ego-facebook.dimacs", "graph_CA-GrQc.dimacs",
        //"graph_ncstrlwg2.dimacs"
    };

    // Create an output file to save the results
    ofstream results_file("results.csv");
    results_file << "Graph,Algorithm,ExecutionTime,SeedSetSize,ActivatedNodes" << endl;

    for (const string& filename : filenames) {
        cout << "Processing " << filename << endl;
        // Read the graph
        vector<vector<int>> G = generate_Graph_from_dimacs("TSS-instances/" + filename);

        // List the algorithms to run
        vector<pair<string, function<vector<int>(const vector<vector<int>>&, double)>> >algorithms = {
            {"greedyIC", greedy_IC},
            {"greedyLT", greedy_LT},
            {"localSearchIC", local_searchIC},
            //{"localSearchLT", local_searchLT},
            {"metaheuristicIC", metaheuristicIC},
            {"metaheuristicLT", metaheuristicLT},
        };

        for (const auto& algorithm : algorithms) {
            // Time the execution of the algorithm
            auto start = chrono::high_resolution_clock::now();
            vector<int> solution;
            try
            {
                solution = algorithm.second(G, 0.5);   /* code */
            }
            catch(const std::exception& e)
            {
                solution = {};
                cout << e.what() << endl;
            }
            
            
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double, milli> execution_time = end - start;

            // Calculate the number of activated nodes
            int activated_nodes = solution.size();

            // Save the results to the CSV file
            results_file << filename << "," << algorithm.first << "," << execution_time.count() << "," << solution.size() << "," << activated_nodes << endl;
        }
    }

    results_file.close();

    return 0;
}

#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <set>
#include <random>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include "graph.h"


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

void visualizeGraph(const vector<vector<int>>& graph,const vector<int>& subset, const string&filename){
    //create directory if it doesn't exist
    mkdir("debug_output/", 0777);
    ofstream dot_file("debug_output/"+filename);

    if (!dot_file.is_open()) {
        cerr << "Failed to open file " << filename << endl;
        return;
    }

    dot_file << "graph G {" << endl;
    
    for (size_t i = 0; i < graph.size(); ++i) {
        dot_file << "  " << i;
        if (find(subset.begin(), subset.end(), i) != subset.end()) {
            dot_file << " [color=red]";
        }
        dot_file << ";" << endl;

        for (const int& neighbor : graph[i]) {
            // To avoid duplicate edges, only print edges where i < neighbor
            if (i < static_cast<size_t>(neighbor)) {
                dot_file << "  " << i << " -- " << neighbor << ";" << endl;
            }
        }
    }

    dot_file << "}" << endl;
    dot_file.close();

    //automatically create png
    string command = "dot -Tpng debug_output/" + filename + " -o debug_output/" + filename + ".png";
    system(command.c_str());
}

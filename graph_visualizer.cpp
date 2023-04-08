#include "graph_visualizer.h"
#include <iostream>
#include <fstream>

using namespace std;

void outputGraphToDotFile(const vector<vector<int>>& graph, const vector<bool>& active_nodes, const string& filename) {
    ofstream dot_file("debug_output/"+filename);

    if (!dot_file.is_open()) {
        cerr << "Failed to open file " << filename << endl;
        return;
    }

    dot_file << "graph G {" << endl;

    /*for (size_t i = 0; i < graph.size(); ++i) {
        for (const int& neighbor : graph[i]) {
            // To avoid duplicate edges, only print edges where i < neighbor
            if (i < static_cast<size_t>(neighbor)) {
                dot_file << "  " << i << " -- " << neighbor;
                if (active_nodes[i] && active_nodes[neighbor]) {
                    dot_file << " [color=red]";
                }
                dot_file << ";" << endl;
            }
        }
    }*/
    for (size_t i = 0; i < graph.size(); ++i) {
        dot_file << "  " << i;
        if (active_nodes[i]) {
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

//Header file for the Graph class
#ifndef METAHEURISTICLT_H
#define METAHEURISTICLT_H

#include <vector>
using namespace std;

vector<vector<int>> generate_graph(int num_nodes, int num_edges);

void visualizeGraph(const vector<vector<int>>& graph, const vector<bool>& active_nodes, const string& filename);

#endif
//Header file for the Graph class
#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
using namespace std;

vector<vector<int>> generate_graph(int num_nodes, int num_edges);

void visualizeGraph(const vector<vector<int>>& graph,const vector<int>& subset, const string&filename);

#endif
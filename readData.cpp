#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "readData.h"
using namespace std;

vector<vector<int>> read_Data(const int& argc, const char* const* argv) {
    if (argc < 2) {
    cout << "Usage: " << argv[0] << " input_file.extension\n";
    }	

    char p;
    string edge;	
    int vertices, edges;

    // Open the input file
    ifstream File(argv[1]); 

    // Read 'p' and 'edge'
    File >> p >> edge; 

    // Read the number of vertices and the number of edges
    File >> vertices >> edges; 

    vector<vector<int>> G(vertices); 

    char e;
    int u, v;

    while (File >> e) {
        if (e == 'e') {
	          // Read an edge (u, v)
            File >> u >> v; 
            // Add v to the adjacency list of u
            G[u-1].push_back(v-1); 
            // Add u to the adjacency list of v
            G[v-1].push_back(u-1); 
        }
    }

    // Close the input file
    File.close(); 

    /*
    // Print the Graph
    for (int u = 0; u < vertices; u++) {
	      cout << u+1 << ": ";
	      for (int v : G[u]) {
	          cout << v+1 << " ";
	      }
	      cout << endl;
    }
    */
    return G;
}

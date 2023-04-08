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

	vector<vector<int>> G(vertices + 1); 

	char e;
	int u, v;

	while (File >> e) {
		  if (e == 'e') {
		  	  // Read an edge (u, v)
		      File >> u >> v; 
		      // Add v to the adjacency list of u
		      G[u].push_back(v); 
		      // Add u to the adjacency list of v
		      G[v].push_back(u); 
		  }
	}

	// Close the input file
	File.close(); 
	
	/*
	
	// Print the Graph
	for (int u = 1; u <= vertices; u++) {
		  cout << u << ": ";
		  for (int v : G[u]) {
		      cout << v << " ";
		  }
		  cout << endl;
	}
	*/
	
	return G;
}

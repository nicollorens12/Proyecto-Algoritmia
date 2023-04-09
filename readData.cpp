#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "readData.h"
using namespace std;

vector<vector<int>> generate_Graph_from_dimacs(string filename) {
    char p, e;
    string edge;    
    int vertices, edges;

    // Open the input file
    ifstream File(filename);
    if (!File) {
        cerr << "Unable to open the file: " << filename << endl;
        exit(1);
    }

    string line;
    while (getline(File, line)) {
        istringstream iss(line);
        iss >> p;
        if (p == 'p') {
            iss >> edge >> vertices >> edges;

            break;
        }
    }

    vector<vector<int>> G(vertices); 
    cout << "vertices: " << vertices << endl;
    cout << "edges: " << edges << endl;

    int u, v;

    while (getline(File, line)) {
        istringstream iss(line);
        if (!(iss >> e)) { // Check if the line is empty or contains unexpected characters
            continue;
        }

        if (e == 'e') {
            // Read an edge (u, v)
            iss >> u >> v; 
            // Add v to the adjacency list of u
            G[u-1].push_back(v-1); 
            // Add u to the adjacency list of v
            G[v-1].push_back(u-1); 
        }
    }

    // Close the input file
    File.close(); 

    return G;
}

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
          G[u-1].emplace_back(v-1); 
          // Add u to the adjacency list of v
          G[v-1].emplace_back(u-1); 
      }
  }

  // Close the input file
  File.close(); 

  return G;
}

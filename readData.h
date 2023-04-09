//Header file for the readData.cpp
#ifndef READDATA_H
#define READDATA_H

#include <vector>
#include <string>

using namespace std;

vector<vector<int> > generate_Graph_from_dimacs(string filename);

vector<vector<int> > read_Data(const int& argc, const char* const* argv);

#endif

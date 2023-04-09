//Header file for the LT metaheuristic
#ifndef METAHEURISTICLT_H
#define METAHEURISTICLT_H

#include <vector>
using namespace std;




vector<int> metaheuristicLT(const vector<vector<int> >& G, const vector<int>& S, double r, int k, int max_generations, int population_size, double mutation_probability, int tournament_size);


#endif

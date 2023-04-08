//Header file for the LT metaheuristic
#ifndef METAHEURISTICLT_H
#define METAHEURISTICLT_H

#include <vector>
using namespace std;



int simulate_LT(const vector<vector<int>>& G, const vector<double>& thresholds, const vector<int>& S);

vector<int> random_solution(int n, int k);

int fitness(const vector<vector<int>>& G, const vector<double>& thresholds, const vector<int>& S, const vector<int>& solution);

vector<int> tournament(const vector<vector<int>>& population, const vector<int>& fitnesses, int tournament_size);

vector<int> single_point_crossover(const vector<int>& parent1, const vector<int>& parent2);

void mutate(vector<int>& solution, int n);

vector<vector<int>> next_generation(const vector<vector<int>>& G, const vector<double>& thresholds, const vector<int>& S, vector<vector<int>>& population, double mutation_probability, int tournament_size);

vector<double> compute_thresholds(const vector<vector<int>>& G);


//actual algorithm
pair<vector<int>, int> metaheuristic(const vector<vector<int>>& G, const vector<int>& S, int k, int max_generations, int population_size, double mutation_probability, int tournament_size) {




#endif

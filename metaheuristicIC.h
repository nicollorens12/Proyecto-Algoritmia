//Header file for the LT metaheuristic
#ifndef METAHEURISTICIC_H
#define METAHEURISTICIC_H

#include <vector>
using namespace std;




vector<int> random_solution(int n, int k);

int fitness(const vector<vector<int>>& G, const vector<int>& S, double p, const vector<int>& solution);

vector<int> tournament(const vector<vector<int>>& population, const vector<int>& fitnesses, int tournament_size);

vector<int> single_point_crossover(const vector<int>& parent1, const vector<int>& parent2);

void mutate(vector<int>& solution, int n);

vector<vector<int>> next_generation(const vector<vector<int>>& G, const vector<int>& S, double r, vector<vector<int>>& population, double mutation_probability, int tournament_size);

//actual algorithm
vector<int> metaheuristicIC(const vector<vector<int>>& G, const vector<int>& S, double r, int k, int max_generations, int population_size, double mutation_probability, int tournament_size);


#endif

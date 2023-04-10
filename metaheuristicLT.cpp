#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <ctime>
#include <cstdlib>
#include "difusioLT.h"
#include "metaheuristicLT.h"
#include "graph.h"

using namespace std;

vector<int> random_solutionLT(int n) {
    int k = rand() % (n / 2) + 1;
    vector<int> solution(k);
    set<int> used;
    for (int i = 0; i < k; i++) {
        int node = rand() % n;
        while (used.count(node) > 0) {
            node = rand() % n;
        }
        solution[i] = node;
        used.insert(node);
    }
    return solution;
}

int fitnessLT(const vector<vector<int>>& G, double r, const vector<int>& solution) {
    int fitnes = G.size() - simulate_LT(G, solution, r);
    return fitnes;
}

vector<int> tournamentLT(const vector<vector<int>>& population, const vector<int>& fitnesses, int tournament_size) {
    int population_size = population.size();
    vector<int> indices(tournament_size);
    for (int i = 0; i < tournament_size; i++) {
        indices[i] = rand() % population_size;
    }
    int best_index = indices[0];
    int best_fitness = fitnesses[indices[0]];
    for (int i = 1; i < tournament_size; i++) {
        if (fitnesses[indices[i]] > best_fitness) {
            best_index = indices[i];
            best_fitness = fitnesses[indices[i]];
        }
    }
    return population[best_index];
}

vector<int> single_point_crossoverLT(const vector<int>& parent1, const vector<int>& parent2) {
    int n = parent1.size();
    int crossover_point = rand() % n;
    vector<int> child(n);
    for (int i = 0; i < crossover_point; i++) {
        child[i] = parent1[i];
    }
    for (int i = crossover_point; i < n; i++) {
        child[i] = parent2[i];
    }
    return child;
}

void mutateLT(vector<int>& solution, int n) {
    int index = rand() % solution.size();
    int new_node = rand() % n;

    while (find(solution.begin(), solution.end(), new_node) != solution.end()) {
        new_node = rand() % n;
    }
    solution[index] = new_node;
}

vector<vector<int>> next_generationLT(const vector<vector<int>>& G, double r, vector<vector<int>>& population, double mutation_probability, int tournament_size) {
    vector<vector<int>> new_population;
    int population_size = population.size();
    vector<int> fitnesses(population_size);
    for (int i = 0; i < population_size; i++) {
        fitnesses[i] = fitnessLT(G, r, population[i]);
    }

    for (int i = 0; i < population_size; i++) {
        vector<int> parent1 = tournamentLT(population, fitnesses, tournament_size);
        vector<int> parent2 = tournamentLT(population, fitnesses, tournament_size);

        vector<int> child = single_point_crossoverLT
    (parent1, parent2);
        if ((double)rand() / RAND_MAX < mutation_probability) {
            mutateLT(child, G.size());
        }

        new_population.push_back(child);
    }

    return new_population;

}


vector<int> metaheuristicLT(const vector<vector<int>>& G, double r) {
    // Number of solutions in a generation
    int population_size = 100;
    double mutation_probability = 0.05;
    int max_generations = 100;
    int tournament_size = 5;

    vector<vector<int>> population(population_size);
    for (int i = 0; i < population_size; i++) {
        population[i] = random_solutionLT
    (G.size());
    }

    for (int i = 0; i < max_generations; i++) {
        population = next_generationLT(G, r, population, mutation_probability, tournament_size);
    }

    int best_fitness = fitnessLT(G, r, population[0]);
    vector<int> best_solution = population[0];
    for (int i = 1; i < population_size; i++) {
        int current_fitness = fitnessLT(G, r, population[i]);
        if (current_fitness> best_fitness) {
            best_fitness = current_fitness;
            best_solution = population[i];
        }
    }
    return best_solution;
}

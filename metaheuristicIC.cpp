#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <queue>
#include "difusioIC.h"

using namespace std;


// Random solution, I think that here we could use the greedy approach to get a initial solution.
vector<int> randomSolution(int n, int k) {
    vector<int> random_solution(n);
    for (int i = 0; i < n; i++) {
        random_solution[i] = i;
    }
    random_shuffle(random_solution.begin(), random_solution.end());
    random_solution.resize(k);
    return random_solution;
}

// Evaluate the quality of the solution.
int fitness(const vector<vector<int>>& G, double p, const vector<int>& S, const vector<int>& solution) {
    vector<int> active(S);
    for (int i : solution) {
        active.push_back(i);
    }
    int fitnes = G.size() - simulate_IC(G, active, p, false);
    return fitnes;
}

// We try to generate a random node that it is not already in the solution.
void mutate(const vector<vector<int>>& G, vector<int>& solution, const double& p) {
    int n = solution.size();
    int index = rand() % n;
    int bestNode = -1;
    int bestCount = -1;
    for (int i = 0; i < G.size(); i++) {
        if (find(solution.begin(), solution.end(), i) == solution.end()) {
            int count = 0;
            for (int j : G[i]) {
                if (find(solution.begin(), solution.end(), j) == solution.end() && ((double) rand() / RAND_MAX) < p) {
                    count++;
                }
            }
            if (count > bestCount) {
                bestNode = i;
                bestCount = count;
            }
        }
    }
    if (bestNode != -1) {
        solution[index] = bestNode;
    }
}

// We select a fixed number of solutions from the population at random and we choose the best solution among them based on their fitness
vector<int> tournament(const vector<vector<int>>& population, const vector<float>& fitnesses, int tournamentSize) {
    int populationSize = population.size();
    vector<int> tournament(tournamentSize);
    for (int i = 0; i < tournamentSize; i++) {
        tournament[i] = rand() % populationSize;
    }
    int bestIndex = tournament[0];
    float bestFitness = fitnesses[tournament[0]];
    for (int i = 1; i < tournamentSize; i++) {
        if (fitnesses[tournament[i]] > bestFitness) {
            bestIndex = tournament[i];
            bestFitness = fitnesses[tournament[i]];
        }
    }
    return population[bestIndex];
}

// We select a candidate with equal probability from parent1 and parent2. Then we we iterate over the child o fix any duplicate 
// nodes by replacing them with nodes that have not been selected.
vector<int> uniformCrossover(const vector<int>& parent1, const vector<int>& parent2) {
    int n = parent1.size();
    vector<int> child(n);
    vector<bool> selected(n, false);
    for (int i = 0; i < n; i++) {
        if (rand() % 2 == 0) {
            child[i] = parent1[i];
            selected[parent1[i]] = true;
        } else {
            child[i] = parent2[i];
            selected[parent2[i]] = true;
        }
    }
    for (int i = 0; i < n; i++) {
        if (selected[child[i]]) {
            selected[child[i]] = false;
        } else {
            for (int j = 0; j < n; j++) {
                if (!selected[j]) {
                    child[i] = j;
                    selected[j] = true;
                    break;
                }
            }
        }
    }
    return child;
}

vector<vector<int>> nextGeneration(const vector<vector<int>>& G, const vector<int>& S, vector<vector<int>>& population, double mutationProbability, int tournamentSize, const double& p) {
    vector<vector<int>> newPopulation;
    int populationSize = population.size();
    
    vector<float> fitnesses(populationSize);
    for (int i = 0; i < populationSize; i++) {
        fitnesses[i] = fitness(G, p, S, population[i]);
    }

    for (int i = 0; i < populationSize; i++) {
        vector<int> parent1 = tournament(population, fitnesses, tournamentSize);
        vector<int> parent2 = tournament(population, fitnesses, tournamentSize);

        vector<int> child = uniformCrossover(parent1, parent2);
        if ((double) rand() / RAND_MAX < mutationProbability) {
            mutate(G, child, p);
        }

        newPopulation.push_back(child);
    }

    return newPopulation;
}

int main() {
	// Number of solutions in a generation
	int populationSize = 100;
	double mutationProbability = 0.05;
	int tournamentSize = 5;
	int k = 3;
	int maxGenerations = 100;

	vector<vector<int>> G = { {1}, {0, 2}, {1, 3}, {2, 4, 5}, {3, 6}, {3, 7}, {4, 8}, {5, 9}, {6}, {7} };
	double p = 0.5;
	vector<int> S = {0, 7, 8};

	vector<vector<int>> population(populationSize);
	for (int i = 0; i < populationSize; i++) {
		  population[i] = randomSolution(G.size(), k);
	}

	// Get generations
	for (int i = 0; i < maxGenerations; i++) {
		  population = nextGeneration(G, S, population, mutationProbability, tournamentSize, p);
	}

	// Get the best solution
	vector<int> bestSolution = population[0];
	float bestFitness = fitness(G, p, S, bestSolution);
	for (int i = 1; i < populationSize; i++) {
		  float currentFitness = fitness(G, p, S, population[i]);
		  if (currentFitness > bestFitness) {
		      bestSolution = population[i];
		      bestFitness = currentFitness;
		  }
	}

	cout << "Best solution: ";
	for (int i : bestSolution) {
		  cout << i << " ";
	}
	cout << endl;
	cout << "Best fitness: " << bestFitness << endl;

}

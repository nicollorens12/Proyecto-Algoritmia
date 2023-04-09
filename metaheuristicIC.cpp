#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <queue>
#include <unordered_set>
#include <chrono>

#include "difusioIC.h"
#include "readData.h"

using namespace std;

// Random solution, I think that here we could use the greedy approach to get a initial solution.
vector<int> randomSolution(const int& graph_size) {
  vector<int> random_solution;
  unordered_set<int> nodes;
  int k = rand() % (graph_size / 2) + 1;
  random_solution.reserve(k);

  while (nodes.size() < k) {
      int node = rand() % graph_size;
      if (nodes.find(node) == nodes.end()) {
          nodes.insert(node);
          random_solution.emplace_back(node);
      }
  }

  return random_solution;
}

// Evaluate the quality of the solution.
int fitness(const vector<vector<int>>& G, double p, const vector<int>& solution) {
  return G.size() - simulate_IC(G, solution, p);
}

// We try to generate a random node that it is not already in the solution.
void mutate(const vector<std::vector<int>>& G, vector<int>& solution, const double& p) {
    int n = solution.size();
    int index = rand() % n;
    int bestNode = -1;
    int bestCount = -1;
    int graph_size = G.size();

    std::unordered_set<int> solutionSet(solution.begin(), solution.end());

    for (int i = 0; i < graph_size; i++) {
        if (solutionSet.find(i) == solutionSet.end()) {
            int count = 0;
            for (int j : G[i]) {
                if (solutionSet.find(j) == solutionSet.end() && ((double)rand() / RAND_MAX) < p) {
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
        solutionSet.erase(solution[index]);
        solutionSet.insert(bestNode);
        solution[index] = bestNode;
    }
}

// We select a fixed number of solutions from the population at random and we choose the best solution among them based on their fitness
vector<int> tournament(const vector<vector<int>>& population, const vector<float>& fitnesses, const int& tournamentSize) {
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

// We select a candidate with equal probability from parent1 and parent2. Then we we iterate over the child and fix any duplicate 
// nodes by replacing them with nodes that have not been selected.
vector<int> uniformCrossover(const vector<int>& parent1, const vector<int>& parent2) {
int n1 = parent1.size();
  int n2 = parent2.size();
  int n = std::min(n1, n2);
  std::vector<int> child(n);
  std::vector<bool> selected(n1 + n2, false);

  // Create a queue of unselected nodes
  std::queue<int> unselected;
  for (int i = 0; i < n1 + n2; i++) {
      unselected.push(i);
  }

  for (int i = 0; i < n; i++) {
      if (rand() % 2 == 0) {
          if (parent1[i] >= 0 && parent1[i] < n1 + n2) {
              child[i] = parent1[i];
              selected[parent1[i]] = true;
              unselected.pop();
          }
      } else {
          if (parent2[i] >= 0 && parent2[i] < n1 + n2) {
              child[i] = parent2[i];
              selected[parent2[i]] = true;
              unselected.pop();
          }
      }
  }
  for (int i = 0; i < n; i++) {
      if (selected[child[i]]) {
          selected[child[i]] = false;
      } else {
          // Get the next unselected node from the queue
          int j = unselected.front();
          unselected.pop();
          if (child[i] == parent1[i]) {
              child[i] = parent2[i];
          } else {
              child[i] = parent1[i];
          }
          selected[j] = true;
      }
  }

  return child;
}

vector<vector<int>> nextGeneration(const vector<vector<int>>& G, const vector<vector<int>>& population, const double& mutationProbability, const int& tournamentSize, const double& p) {
  vector<vector<int>> newPopulation;
  int populationSize = population.size();

  vector<float> fitnesses(populationSize);
  for (int i = 0; i < populationSize; i++) {
      fitnesses[i] = fitness(G, p, population[i]);
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


/*
int main(int argc, char **argv) {
  // Number of solutions in a generation
  int populationSize = 100;
  double mutationProbability = 0.05;
  int maxGenerations = 100;
  int tournamentSize = 5;

  vector<vector<int>> G = read_Data(argc, argv);
  int graph_size = G.size();

  double p = 0.5;
  
  auto start = std::chrono::high_resolution_clock::now();

  vector<vector<int>> population;
  population.reserve(populationSize);
  for (int i = 0; i < populationSize; i++) population.emplace_back(randomSolution(graph_size));

  // Get generations
  for (int i = 0; i < maxGenerations; i++) {
		  population = nextGeneration(G, population, mutationProbability, tournamentSize, p);
  }

  // Get the best solution
  vector<int> bestSolution = population[0];
  int bestFitness = fitness(G, p, bestSolution);
  for (int i = 1; i < populationSize; i++) {
		  float currentFitness = fitness(G, p, population[i]);
		  if (currentFitness < bestFitness) {
		      bestSolution = population[i];
		      bestFitness = currentFitness;
		  }
  }
  
  auto end = std::chrono::high_resolution_clock::now();
  
  auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  
  cout << "Execution time: " << elapsed_time.count() << " ms" << std::endl;

  cout << "Best solution: {";
  int bestSolution_size = bestSolution.size();
  for (int i = 0; i < bestSolution_size; ++i) {
      if(i == bestSolution_size - 1) cout << bestSolution[i] + 1;
      else cout << bestSolution[i] + 1 << ", ";
  }
  cout << "}" << endl;
  cout << "Best fitness: " << bestFitness << endl;

}
*/
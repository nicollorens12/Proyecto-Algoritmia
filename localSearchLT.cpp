#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <random>
#include "difusioLT.h"
#include "readData.h"

using namespace std;

// Helper function to generate a neighbor solution
vector<int> generate_neighbor_solution(const vector<int>& S, int n, int k) {
    vector<int> neighbor_solution = S;

    for (int i = 0; i < k; i++) {
        int random_node = rand() % n;
        neighbor_solution[random_node] = 1 - neighbor_solution[random_node];
    }

    return neighbor_solution;
}

vector<int> simulated_annealing(const vector<vector<int>>& G, double r, int max_iter, double T_start, double T_end, double alpha, int k) {
    int n = G.size();
    srand(time(0));

    // Generate initial solution
    vector<int> current_solution(n, 0);
    for (int i = 0; i < n; i++) {
        current_solution[i] = rand() % 2;
    }

    int best_score = simulate_LT(G, current_solution, r);
    vector<int> best_solution = current_solution;

    double T = T_start;

    for (int iter = 0; iter < max_iter; iter++) {
        vector<int> neighbor_solution = generate_neighbor_solution(current_solution, n, k);
        int neighbor_score = simulate_LT(G, neighbor_solution, r);

        int current_score = simulate_LT(G, current_solution, r);
        int delta = neighbor_score - current_score;

        // Add a penalty for larger sets
        int penalty = count(neighbor_solution.begin(), neighbor_solution.end(), 1) - count(current_solution.begin(), current_solution.end(), 1);
        delta -= penalty;

        if (delta > 0 || exp(delta / T) > (double)rand() / RAND_MAX) {
            current_solution = neighbor_solution;
        }

        if (neighbor_score > best_score || (neighbor_score == best_score && penalty > 0)) {
            best_score = neighbor_score;
            best_solution = neighbor_solution;
        }

        T = T * alpha;
        if (T < T_end) break;
    }

    return best_solution;
}


vector<int> local_searchLT(vector<vector<int> > G, double r) {
    int max_iter = 10000;
    double T_start = 1000;
    double T_end = 1e-9;
    double alpha = 0.99;
    int k = 2;
    
    vector<int> S = simulated_annealing(G, r, max_iter, T_start, T_end, alpha, k);
    vector<int> Solution;
    int set_size = S.size();
    for (int i = 0; i < set_size; i++) {
        if (S[i]) Solution.emplace_back(i);
    }
    
    return Solution;
}

int main(int argc, char **argv){
    vector<vector<int>> G = read_Data(argc, argv);
    double r = 0.5;

    vector<int> S = local_searchLT(G, r);
    
    for(auto i:S) cout << i+1 << " ";
    
    cout << "SIZE " << S.size();
}


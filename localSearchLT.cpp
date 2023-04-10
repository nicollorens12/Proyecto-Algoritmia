#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <random>
#include <algorithm>
#include "difusioLT.h"

using namespace std;

random_device rd;
mt19937 gen(rd());

int rand_node(int V) {
    uniform_int_distribution<> distribucion(0, V - 1);
    return distribucion(gen);
}

vector<int> random_set(int V, double r) {
    vector<int> aux;
    uniform_real_distribution<double> dis(0.0, 1.0);

    for (int i = 0; i < V; i++) {
        double p = dis(gen);

        if (p < r) {
            aux.push_back(i);
        }
    }
    return aux;
}

int sol_score(vector<int> sol, int V) {
    int sol_size = sol.size();
    return (100 / V) * (V - sol_size);
}

vector<int> generate_neighbor(vector<int> sol, vector<bool>& active, int V) {
    int random_number = rand_node(V);
    while (!active[random_number]) {
        random_number = rand_node(V);
    }
    active[random_number] = false;
    sol.erase(remove(sol.begin(), sol.end(), random_number), sol.end());
    return sol;
}

bool its_valid(const vector<vector<int> >& G, const vector<int>& sol, double r) {
    int V = G.size();
    vector<int> S(sol);
    return simulate_LT(G, S, r) == V;
}

bool more_degree(const vector<int>& S, const vector<int>& neighbor, const vector<vector<int> >& G) {
    int s_counter = 0;
    int neighbor_counter = 0;
    for (int i : S) {
        s_counter += G[i].size();
    }
    for (int i : neighbor) {
        neighbor_counter += G[i].size();
    }
    return neighbor_counter > s_counter;
}

bool is_updated(const vector<int>& S, const vector<int>& new_S) {
    return !equal(S.begin(), S.end(), new_S.begin());
}

vector<int> local_searchLT(vector<vector<int> > G, double r) {
    int max_iterations = 1000;
    double initial_temperature = 100.0;
    double cooling_rate = 0.99;
    int V = G.size();

    vector<int> rand_set = random_set(V, r);
    vector<bool> active(V, false);

    while (rand_set.empty() || !its_valid(G, rand_set, r)) {
        rand_set = random_set(V, r);
    }

    vector<int> S = rand_set;

    for (int i : S) {
        active[i] = true;
    }
    int quality = sol_score(S, V);
    int iteration = 0;
    double temperature = initial_temperature;

    while (iteration < max_iterations && quality < V) {
        vector<int> neighbor_S = generate_neighbor(S, active, V);
        int neighbor_quality = sol_score(neighbor_S, V);

        if (its_valid(G, neighbor_S, r) && (neighbor_quality > quality || (neighbor_S.size() == S.size() && more_degree(S, neighbor_S, G)))) {
            S = neighbor_S;
            quality = neighbor_quality;
        }   else {
            double acceptance_probability = exp((neighbor_quality - quality) / temperature);
            if (acceptance_probability > (double)rand() / RAND_MAX) {
                S = neighbor_S;
                quality = neighbor_quality;
            }
        }

        temperature = temperature * cooling_rate;
        iteration++;

        // Break the loop if the solution hasn't been updated for a certain number of iterations
        if (!is_updated(S, neighbor_S)) {
            break;
        }
    }

    return S;
}

#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <random>
#include "difusioLT.h"

using namespace std;


int rand_node(int V){

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distribucion(0, V - 1);
    return distribucion(gen);

}

vector<int> random_set(int V, double r){
    vector<int> aux;

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(0.0, 1.0);

    for (int i = 0; i < V; i++) {

        double p = dis(gen);

        if (p < r) {
            aux.push_back(i);
        }
    }
    return aux;
}

int sol_score(vector<int> sol, int V){ //Implementacion provisional con nota en vez de solo size por si se decide añadir mas parametros al score
    int sol_size = sol.size();
    return (100/V) * (V - sol_size); //Cuanto menos nodos mas nota de 0 a 100

}

vector<int> generate_neighbor(vector<int> sol,vector<bool>& active, int V){ //Kill an active node

    int random_number = rand_node(V);
    while(!active[random_number]){
        random_number = rand_node(V);
    }
    active[random_number] = false;
    int i = 0;
    bool found = false;
    int sol_size = sol.size();
    while(i < sol_size and not found) if(sol[i] == random_number) sol.erase(sol.begin()+i);
    return sol;
}

bool its_valid(const vector<vector<int>> G, const vector<int> sol, double r){

    int V = G.size();
    vector<int> S(sol);
    if( simulate_LT(G,S,r, false) != V ) return false;
    return true;
}

bool more_degree(const vector<int>& S, const vector<int>& neighbor, const vector<vector<int>>& G){ //this function is only accessed when size is the same
    int size = neighbor.size();
    int s_counter = 0;
    int neighbor_counter = 0;
    for(int i = 0; i < size; ++i ){
        neighbor_counter += G[neighbor[i]].size();
        s_counter += G[S[i]].size();
    }
    return neighbor_counter > s_counter;
}

vector<int> add_active(vector<int>& set,vector<bool> active, int V){
    int random_number = rand_node(V);
    while(active[random_number]){
        random_number = rand_node(V);
    }
    active[random_number] = true;
    set.push_back(random_number);
    return set;
}

void local_search(vector<vector<int>> G, double r){
    int max_iterations = 1000;
    double initial_temperature = 100.0;
    double cooling_rate = 0.99;
    int V = G.size();

    vector<int> rand_set = random_set(V,r);
    vector<bool> active = vector<bool>(G.size(),false);

    while(!its_valid(G,rand_set,r))
        rand_set = add_active(rand_set,active,V);
    vector<int> S = rand_set;

    int S_size = S.size();

    for(int i = 0; i < S_size; ++i) active[S[i]] = true;
    int quality = sol_score(S,V);
    int iteration = 0;
    double temperature = initial_temperature;

    while(iteration < max_iterations and quality < V ){
        vector<int> neighbor_S = generate_neighbor(S,active,V);
        int neighbor_quality = sol_score(neighbor_S,V);

        if ((neighbor_quality > quality or (neighbor_S.size() == S.size() and more_degree(S,neighbor_S,G))) and its_valid(G,neighbor_S,r)) { //when same quantity of active nodes, priorize the solution that affects more nodes
            S = neighbor_S;
            quality = neighbor_quality;
        }
        else {
            double acceptance_probability = exp((neighbor_quality - quality) / temperature);
            if (acceptance_probability > (double)rand() / RAND_MAX) {
                S = neighbor_S;
                quality = neighbor_quality;
            }
        }

        temperature = temperature * cooling_rate;
        iteration++;
    }

    cout << "-------------LOCAL SEARCH-------------" << endl;
    cout << "MINIMUM INITIAL NODES: {";
    S_size = S.size();
    for(int k = 0; k < S_size; ++k) {
        if(k == S_size- 1) cout << S[k];
        else cout << S[k] << ", ";
    }
    cout << "}" << endl;
    cout << "With an R of: " << r << endl;

}

int main(){
    vector<vector<int> > G = { {1}, {0, 2}, {1, 3}, {2, 4, 5}, {3, 6}, {3, 7}, {4, 8}, {5, 9}, {6}, {7} };
    double r = 0.6;

    local_search(G,r);


}
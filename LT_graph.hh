#ifndef LT_GRAPH_HH
#define LT_GRAPH_HH

#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <random>

using namespace std;

struct node_info{
    int node;
    int degree;
};

class LTGraph{

    private:
        vector<vector<int>> G;
        double r;
        vector<int> S;
        vector<bool> active;
    public:

    LTGraph(vector<vector<int> > graph, vector<int> S_a, float r_a){
        G = graph;
        r = r_a;
        S = S_a;
        active = vector<bool> (G.size(),false); //Not used
    }

    LTGraph(vector<vector<int> > graph, float r_a){
        G = graph;
        r = r_a;
        active = vector<bool> (G.size(),false);
    }

    int procedure(){
        // Initialize counter as number of active nodes
        int counter = S.size();
        int V = G.size();
        vector<bool> active(V, false);

        for (int node : S) {
            active[node] = true;
        }

        // 2 conditions to end loop. Either:
        // all nodes are activated
        // no new nodes have been activated since the last pass
        while (counter < V) {
            // store number of active nodes:
            int initial = counter;

            for (int i=0; i<V; i++) {
                // for all inactive nodes, check neighbor influence:
                if (!active[i]) {
                    // threshold = r * degree
                    double threshold = r * G[i].size();

                    // add influence of each active neighbor:
                    int influence = 0;
                    for (int neighbor : G[i]) {
                        if(active[neighbor]) {
                            influence++;
                        }
                        // if influence surpasses threshold,
                        if(influence >= threshold) {
                            active[i] = true;
                            counter++;
                            break;
                        }
                    }
                }
            }
            // check to see if there were new activations:
            if (counter == initial) {
                break;
            }
        }

        return counter;
    }
    static bool node_comparator(node_info n1, node_info n2){
        return n1.degree < n2.degree;
    }

    void greedy(){

        int V = G.size();
        S = vector<int> (V);
        for(int i = 0; i < V; ++i) S[i] = i;
        vector<node_info> degree(V);

        for(int i = 0; i < V; ++i) {
            degree[i].node = i;
            degree[i].degree = G[i].size();
        }
        sort(degree.begin(),degree.end(), node_comparator);
        bool stop = false;
        int e_degree = 0;
        vector<int> old_S;
        while(!stop){

            vector<int> aux;
            for(int j = e_degree; j < V; ++j) aux.push_back(degree[j].node);

            //si aux es vacio ni intentar
            old_S = S;
            S = aux;
            int procedure_res = procedure();
            if(procedure_res != V) stop = true;
            else ++e_degree;

        }
        cout << "-------------GREEDY-------------" << endl;
        cout << "MINIMUM INITIAL NODES: {";
        int old_S_size = old_S.size();
        for(int k = 0; k < old_S_size; ++k) {
            if(k == old_S_size - 1) cout << old_S[k];
            else cout << old_S[k] << ", ";
        }
        cout << "}" << endl;
    }

    int rand_node(){
        int V = G.size();
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distribucion(0, V - 1);
        return distribucion(gen);

    }

    vector<int> random_set(){
        vector<int> aux;

        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<double> dis(0.0, 1.0);
        int V = G.size();
        for (int i = 0; i < V; i++) {

            double p = dis(gen);

            if (p < r) {
                aux.push_back(i);
            }
        }
        return aux;
    }

    static int sol_score(vector<int> sol, int V){ //Implementacion provisional con nota en vez de solo size por si se decide añadir mas parametros al score
      int sol_size = sol.size();
      return (100/V) * (V - sol_size); //Cuanto menos nodos mas nota de 0 a 100

    }

    vector<int> generate_neighbor(){ //Kill an active node
        vector<int> sol = S;
        int random_number = rand_node();
        while(!active[random_number]){
            random_number = rand_node();
        }
        active[random_number] = false;
        int i = 0;
        bool found = false;
        int sol_size = sol.size();
        while(i < sol_size and not found) if(sol[i] == random_number) sol.erase(sol.begin()+i);
        return sol;
    }

    bool its_valid(vector<int> sol){
        S = sol;
        int V = G.size();
        if( this->procedure() != V ) return false;
        return true;
    }

    bool more_degree(vector<int> neighbor){ //this function is only accessed when size is the same
        int size = neighbor.size();
        int s_counter = 0;
        int neighbor_counter = 0;
        for(int i = 0; i < size; ++i ){
            neighbor_counter += G[neighbor[i]].size();
            s_counter += G[S[i]].size();
        }
        return neighbor_counter > s_counter;
    }

    vector<int> add_active(vector<int>& set){
        int random_number = rand_node();
        while(active[random_number]){
            random_number = rand_node();
        }
        active[random_number] = true;
        set.push_back(random_number);
        return set;
    }

    void local_search(){
        int max_iterations = 1000;
        double initial_temperature = 100.0;
        double cooling_rate = 0.99;
        vector<int> rand_set = random_set();
        while(!its_valid(rand_set))
            rand_set = add_active(rand_set);
        S = rand_set;
        int V = G.size();
        int S_size = S.size();
        for(int i = 0; i < S_size; ++i) active[S[i]] = true;
        int quality = sol_score(S,V);
        int iteration = 0;
        double temperature = initial_temperature;

        while(iteration < max_iterations and quality < V ){
            vector<int> neighbor_S = generate_neighbor();
            int neighbor_quality = sol_score(neighbor_S,V);

            if ((neighbor_quality > quality or (neighbor_S.size() == S.size() and more_degree(neighbor_S))) and its_valid(neighbor_S)) { //when same quantity of active nodes, priorize the solution that affects more nodes
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

    }
};

#endif


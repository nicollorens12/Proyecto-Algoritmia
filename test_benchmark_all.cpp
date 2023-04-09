#include <string>
#include "graph.h"
#include "greedyIC.h"
#include "greedyLT.h"
#include "localSearchLT.h"
#include "localSearchIC.h"
#include "metaheuristicLT.h"
#include "metaheuristicIC.h"
#include "readData.h"

using namespace std;

int main(int argc, char* argv[]) {
    //pass a file name as an argument
    //default is dolphins
    string filename = "TSS-instances/graph_dolphins.dimacs";
    if (argc > 1) {
        filename = "TSS-instances/"+string(argv[1]);
    }

    double p = 0.5;
    double r = 0.5;


    //generate and visualize graph
    vector<vector<int>> G = generate_Graph_from_dimacs(filename);
    visualizeGraph(G, {}, string("graph.dot"));

    //run greedyIC
    vector<int> greedyIC_solution = greedy_IC(G,p);
    visualizeGraph(G, greedyIC_solution, string("greedyIC.dot"));

    //run greedyLT
    vector<int> greedyLT_solution = greedy_LT(G,r);
    visualizeGraph(G, greedyLT_solution, string("greedyLT.dot"));

    //run localSearchIC
    vector<int> localSearchIC_solution = local_searchIC(G,p);
    visualizeGraph(G, localSearchIC_solution, string("localSearchIC.dot"));

    //run localSearchLT
    vector<int> localSearchLT_solution = local_searchLT(G,r);
    visualizeGraph(G, localSearchLT_solution, string("localSearchLT.dot"));

    //run metaheuristicIC
    //vector<int> metaheuristicIC_solution = metaheuristic_IC(G,p);
    //visualizeGraph(G, metaheuristicIC_solution, string("metaheuristicIC.dot"));

    //run metaheuristicLT
    //vector<int> metaheuristicLT_solution = metaheuristicLT(G,r);
    //visualizeGraph(G, metaheuristicLT_solution, string("metaheuristicLT.dot"));

}

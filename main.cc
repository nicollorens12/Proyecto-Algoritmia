#include <vector>
#include <iostream>
#include "LT_graph.hh"
#include "IC_graph.hh"

using namespace std;

int main(){
    vector<vector<int> > G = { {1}, {0, 2}, {1, 3}, {2, 4, 5}, {3, 6}, {3, 7}, {4, 8}, {5, 9}, {6}, {7} };
    //double p = 0.8;
    double r = 0.6;

    /* PROCEDURE TESTING
    vector<int> S = {0, 7, 8};
    LTGraph LT( G, S, r);
    ICGraph IC(G, S, p);
    cout << "With an LT procedure there are " << LT.procedure() << " node(s) active(s) with a R of " << r << endl;
    cout << endl;
    cout << "With an IC procedure there are " << IC.procedure() << " node(s) active(s) with a P of " << p << endl;
     */
    LTGraph LT(G,r);
    LT.greedy();
}


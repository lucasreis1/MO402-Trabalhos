#include "Graph_A.hpp"
#include<vector>

using std::vector;

Graph_A g_linha(Graph_A &G);

void initialize_matrix(vector<vector<double>> &D, int n_vert);

vector<vector<int>> Johnson(Graph_A &G, vector<vector<double>> &d, int op);
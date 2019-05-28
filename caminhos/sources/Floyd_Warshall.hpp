#include "Graph_M.hpp"
#include<vector>

using std::vector;

void initialize_sp_matrix(vector<vector<double>> &D, int n_vert);
void initialize_pr_matrix(vector<vector<int>> &P, int n_vert);
void initialize_sp_weights(vector<vector<double>> &D, Graph_M &G);
vector<vector<int>> Floyd_Warshall(Graph_M &G, int op, vector<vector<double>> &d);
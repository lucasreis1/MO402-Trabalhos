#include "Graph_M.hpp"
#include<vector>

using std::vector;

void initialize_sp_matrix(vector<vector<double>> &D, Graph_M &G, int n_vert);
void initialize_pr_matrix(vector<vector<int>> &P, int n_vert);
vector<vector<int>> Floyd_Warshall(Graph_M &G, int op, vector<vector<double>> &d);
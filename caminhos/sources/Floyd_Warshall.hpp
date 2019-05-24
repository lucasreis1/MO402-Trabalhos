#include "Graph_M.hpp"
#include<vector>

using std::vector;

void initialize_sp_matrix(vector<vector<float>> &D, int n_vert);
void initialize_pr_matrix(vector<vector<int>> &P, int n_vert);
void initialize_sp_weights(vector<vector<float>> &D, Graph_M &G);
void print_sp_matrix(vector<vector<float>> &D, int n_vert);
void print_pr_matrix(vector<vector<int>> &D, int n_vert);
vector<vector<int>> Floyd_Warshall(Graph_M &G, int op, vector<vector<float>> &d);
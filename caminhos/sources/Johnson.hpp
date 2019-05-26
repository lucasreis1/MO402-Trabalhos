#include "Graph_A.hpp"
#include<vector>

using std::vector;
//typedef vector< vector<double> > Matrix;
typedef double** Matrix;

Graph_A g_linha(Graph_A &G);
vector<vector<int>> Johnson(Graph_A &G, vector<int> &pred, vector<double> &costs, Matrix D, int op, int n_vert);
void initialize_pr_matriz(vector<vector<int>> &P, int n_vert);
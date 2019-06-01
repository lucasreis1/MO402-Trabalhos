#include "Graph.hpp"

typedef Graph::Edge Edge;

bool maximal_path_dfs(Graph &G, int s,int t, vector<Edge *> &path, int &cp);

int ford_fulkerson(Graph &G,int s,int t);
#include "Graph.hpp"

typedef Graph::Edge Edge;

bool maximal_path_bfs(Graph &G, int s,int t, vector<Edge *> &path, int &cp);

int edmonds_karp(Graph &G,int s,int t);
#include "Graph.hpp"

typedef Graph::Edge Edge;

bool layers(Graph &G, vector<int> &layer, const int &s, const int &t);

bool find_path(Graph &G, vector<int> &layer, vector<Edge *> &S, const int &u, const int &t);

void increase_flow(Graph &G, vector<Edge *> &S);

bool maximal(Graph &G, vector<int> &layer, const int &s, const int &t);

int Dinitz(Graph &G, int s, int t);
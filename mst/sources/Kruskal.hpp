#include "Graph.hpp"
#include "Union_Find_Vector.hpp"
#include "Union_Find_LL.hpp"
#include "Union_Find_Tree.hpp"

bool sort_function(Edge *a, Edge *b);

Union_Find * create_uf_struct(int op,int size);

vector<Edge> Kruskal(Graph &G, int op, double &cost);
#include "flow_dep.hpp"

int maximum_flow(Graph &G, int s)
{
	int max_flow = 0;
	for(vector<Edge *>::iterator it = G.vertices[s].edg.begin() ; it < G.vertices[s].edg.end() ; ++it)
	{
		Edge *e = *it;
		max_flow += e->f;
	}
	return max_flow;
}
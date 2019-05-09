#include "Prim.hpp"

vector<Edge> Prim(Graph &G, int op, float &cost, int src)
{
	vector<Edge> A;
	vector<Edge> Pi(G.n_vert);
	cost = 0;
	Heap Hp(G.n_vert,src);
	while(Hp.tam > 0)
	{
		int u = Hp.extract_min();
		vector<Edge *> adj = G.vertices[u].edg;
		int nadj = G.vertices[u].n_edges;
		for(int i = 0 ; i < nadj ; i++)
		{
			int viz = (adj[i]->va == u?adj[i]->vb:adj[i]->va);
			if(Hp.in_queue(viz) && adj[i]->wgt < Hp.get_value(viz))
			{
				Hp.decrease_key(viz,adj[i]->wgt);
				Pi[viz] = *adj[i];
			}
		}
		if(u != src)
		{
			A.push_back(Pi[u]);
			cost += Pi[u].wgt;
		}
	}
	return A;
}
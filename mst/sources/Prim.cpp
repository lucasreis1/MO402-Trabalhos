#include "Prim.hpp"
#include <iostream>

Queue * create_priority_queue(int op, int size, int src)
{
    Queue * Q = NULL;
    switch(op)
    {
        case 0:
        {
            Q = new Heap(size, src);
            break;
        }
        case 1:
        {
            Q = new NaivePriorityQueue(size, src);
            break;
        }
        case 2:
        {
            /*Fibonacci Heaps*/
            break;
        }
        default:
            std::cerr << "Opção inválida" << std::endl;
            exit(1);
    }

    return Q;
}

vector<Edge> Prim(Graph &G, int op, float &cost, int src)
{
	vector<Edge> A;
	vector<Edge> Pi(G.n_vert);
	cost = 0;
	Queue * Q = create_priority_queue(op, G.n_vert, src);
	while(Q->tam > 0)
	{
		int u = Q->extract_min();
		vector<Edge *> adj = G.vertices[u].edg;
		int nadj = G.vertices[u].n_edges;
		for(int i = 0 ; i < nadj ; i++)
		{
			int viz = (adj[i]->va == u?adj[i]->vb:adj[i]->va);
			if(Q->in_queue(viz) && adj[i]->wgt < Q->get_value(viz))
			{
				Q->decrease_key(viz,adj[i]->wgt);
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
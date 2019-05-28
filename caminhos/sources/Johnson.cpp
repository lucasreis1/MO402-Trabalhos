#include "Johnson.hpp"
#include "Bellman_Ford.hpp"
#include "Dijkstra.hpp"
#include<iostream>

Graph_A g_linha(Graph_A &G)
{
	int s;
	Graph_A G_linha(G);

	s = G_linha.add_vert();

	for(int i = 0; i < G.n_vert; i++)
		G_linha.add_edge(s, i, 0.0);

	return G_linha;
}

void initialize_matrix(vector<vector<double>> &D, int n_vert)
{
    D.resize(n_vert);
    for (int i = 0; i < n_vert; ++i)
    {
        D[i].resize(n_vert);
    }
}

vector<vector<int>> Johnson(Graph_A &G, vector<vector<double>> &d, int op)
{
	Graph_A G_linha = g_linha(G);
	vector<vector<int>> p_n(G.n_vert ,vector<int> (G.n_vert,-1));
	vector<int> pred(G.n_vert,-1);
	vector<double> h(G.n_vert);
	vector<double > w_;

	initialize_matrix(d,G.n_vert);
	if(Bellman_Ford(G_linha, G_linha.n_vert-1, pred, h))
		std::cout << "O grafo contém um ciclo de peso negativo" << std::endl;
	else
	{
		for(int i = 0; i < G.n_edges; i++)
		{
			int u,v;
			u = G.edges[i]->va;
			v = G.edges[i]->vb;
			G.edges[i]->wgt = G.edges[i]->wgt + h[u] - h[v];
		}
		for(int i = 0 ; i < G.n_vert; i++)
		{
			p_n[i] = Dijkstra(G, op, i, w_);
			for(int j = 0 ; j < G.n_vert; j++)
				d[i][j] = w_[j] + h[j] - h[i];
		}
	}
	return p_n;
}
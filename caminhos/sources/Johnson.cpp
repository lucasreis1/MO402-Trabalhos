#include "Johnson.hpp"
#include "Bellman_Ford.hpp"
#include "Dijkstra.hpp"
#include<iostream>

Graph_A g_linha(Graph_A &G)
{
	int s;
	Graph_A G_linha(G.n_vert);

	G_linha = G;

	s = G_linha.add_vert();

	for(int i; i < G.n_vert; i++)
		G_linha.add_edge(s, i, 0.0);

	return G_linha;
}

void initialize_pr_matriz(vector<vector<int>> &P, int n_vert)
{
    P.resize(n_vert);
    for (int i = 0; i < n_vert; ++i)
    {
        P[i].resize(n_vert);
    }
}

vector< vector<int> > Johnson(Graph_A &G, vector<int> &pred, vector<double> &costs, Matrix D, int op, int n_vert)
{
	const size_t V = n_vert;
	Graph_A G_linha = g_linha(G);
	vector<double> w_;
	double h[V];
	vector<vector<int>> p_n;

	initialize_pr_matriz(p_n, n_vert);
	pred.resize(n_vert);
	costs.resize(n_vert);


	if(Bellman_Ford(G_linha, G_linha.vertices[G_linha.n_vert-1].number, pred, costs))
		std::cout << "O grafo contém um ciclo de peso negativo" << std::endl;
	else
	{
		for(int i = 0 ; i < G_linha.n_vert-1; i++)
			h[i] = costs[i];
		
		for(int i = 0; i < G_linha.n_edges; i++)
			w_.push_back(G_linha.edges[i]->wgt + h[G_linha.edges[i]->va] - h[G_linha.edges[i]->vb]);
			
	
		for(size_t i = 0 ; i < V; i++)
		{
			p_n[(int)i] = Dijkstra(G, op, (int)i, w_);
			for(size_t j = 0 ; j < V; j++){
				D[i][j] = w_[j] + h[i] - h[j];
			}
		}
	}
	return p_n;
}
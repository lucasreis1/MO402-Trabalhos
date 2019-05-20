#include "Graph_M.hpp"
#include<iostream>

Graph_M::Graph_M(int nver): Graph(nver)
{
	edges.resize(n_vert);
	for(int i = 0 ; i < n_vert ; i++)
	{
		edges[i].resize(n_vert);
		edges[i][i].exist = true;
	}
}

int Graph_M::add_vert()
{
	n_vert++;
	edges.resize(n_vert);
	for(int i = 0 ; i < n_vert ; i++)
		edges[i].resize(n_vert);
	return n_vert-1;
}

void Graph_M::add_edge(int va,int vb,float w)
{
	if(va >= n_vert || vb >= n_vert)
	{
		std::cerr << "Vértice inválido para inserção" << std::endl;
		exit(1);
	}
	edges[va][vb].exist = true;
	edges[va][vb].w = w;
}

void Graph_M::print_edges()
{
	for(int i = 0 ; i < n_vert ; i++)
	{
		for(int j = 0 ; j < n_vert ; j++)
		{
			if(edges[i][j].exist)
				std::cout << edges[i][j].w;
			else
				std::cout << "INF";
			std::cout << '\t';
		}
		std::cout << std::endl;
	}
}
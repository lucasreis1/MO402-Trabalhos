#include "Graph_A.hpp"
#include<iostream>
#include <cstddef>

Graph_A::Graph_A(int nver): Graph(nver), vertices(n_vert)
{
	for(int i = 0 ; i < n_vert ; i++)
		vertices[i].number = i;
}

Graph_A::~Graph_A()
{
	for(int i = 0 ; i < n_edges ; i++)
		delete edges[i];
}

int Graph_A::add_vert()
{
	n_vert++;
	vertices.resize(n_vert,Vertex(n_vert-1));
	return n_vert-1;
}

void Graph_A::add_edge(int va, int vb, double w)
{
	if(va < n_vert && vb < n_vert)
	{
		Edge *new_e = new Edge(va,vb,w);
		edges.push_back(new_e);
		n_edges++;
		vertices[va].edg.push_back(new_e);
		vertices[va].n_edges++;
	}
	else
	{
		std::cerr << "Vértice inexistente" << std::endl;
		exit(1);
	}
}

void Graph_A::print()
{
	for(int i = 0 ; i < n_vert ; i++)
	{
		for(int j = 0 ; j < vertices[i].n_edges ; j++)
		{
			std::cout << vertices[i].edg[j]->va << " " << vertices[i].edg[j]->vb << " " << vertices[i].edg[j]->wgt;
			std::cout << std::endl;
		}
	}
}
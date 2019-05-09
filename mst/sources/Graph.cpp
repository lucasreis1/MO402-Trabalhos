#include "Graph.hpp"
#include<iostream>


Graph::Graph(int nver): n_vert(nver), n_edges(0), vertices(n_vert)
{
	for(int i = 0 ; i < n_vert ; i++)
		vertices[i].number = i;
}

Graph::~Graph()
{
	for(int i = 0 ; i < n_edges ; i++)
		delete edges[i];
}

void Graph::add_vert()
{
	n_vert++;
	vertices.resize(n_vert,Vertex(n_vert-1));
}

void Graph::add_edge(int va, int vb, float w)
{
	if(va < n_vert && vb < n_vert)
	{
		Edge *new_e = new Edge(va,vb,w);
		edges.push_back(new_e);
		n_edges++;
		vertices[va].edg.push_back(new_e);
		vertices[vb].edg.push_back(new_e);
		vertices[va].n_edges++;
		vertices[vb].n_edges++;
	}
	else
	{
		std::cerr << "Vértice inexistente" << std::endl;
		exit(1);
	}
}



void Graph::print_graph()
{
	for(int i = 0 ; i < n_vert ; i++)
	{
		std::cout << "Vértice " << i << ':' << std::endl;
		for(int j = 0 ; j < vertices[i].n_edges; j++)
		{
			if(j)
				std::cout << " // ";
			std::cout << "va:" << vertices[i].edg[j]->va << " vb:" << vertices[i].edg[j]->vb << " weight:" << vertices[i].edg[j]->wgt;
		}
		std::cout << std::endl;
	}
}

void Graph::print_edges()
{
	std::cout << "Edges:" << std::endl;
	for(int i = 0 ; i < n_edges ; i++)
		std::cout << "va:" << edges[i]->va << ' ' << " vb:" << edges[i]->vb << " weight:" << edges[i]->wgt<< std::endl;
}
#include "Graph.hpp"
#include<iostream>

typedef Graph::Edge Edge;
typedef Graph::Vertex Vertex;

Graph::Graph(int nver): n_vert(nver), n_edges(0), vertices(n_vert)
{
	for(int i = 0 ; i < n_vert ; i++)
		vertices[i].number = i;
}

Graph::~Graph()
{
	for(unsigned int i = 0 ; i < edges.size() ; i++)
		delete edges[i];
}

void Graph::add_vert()
{
	n_vert++;
	vertices.resize(n_vert,Vertex(n_vert-1));
}

void Graph::add_edge(int va, int vb, int cap)
{
	if(va < n_vert && vb < n_vert)
	{
		Edge *new_fe = new Edge(va,vb,cap,0,cap,edges.size()+1,false,false); // forward edge
        	Edge *new_be = new Edge(vb,va,cap,0,0,edges.size(),false,true); // back edge
	        edges.push_back(new_fe);
	        edges.push_back(new_be);
		n_edges+=2;
		vertices[va].edg.push_back(new_fe);
	        vertices[vb].edg.push_back(new_be);
		vertices[va].n_edges++;
	        vertices[vb].n_edges++;
	}
	else
	{
		std::cerr << "Vértice inexistente" << std::endl;
		exit(1);
	}
}


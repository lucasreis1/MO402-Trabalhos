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
	for(int i = 0 ; i < n_edges ; i++)
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

void Graph::print_graph()
{
    int init;
	for(int i = 0 ; i < n_vert ; i++)
	{
		std::cout << "Vértice " << i << ':' << std::endl;
		init = 0;
		for(int j = 0 ; j < vertices[i].n_edges ; j++)
		{
			if (!vertices[i].edg[j]->back) {
                if(init++)
                    std::cout << " // ";
			    std::cout << "va:" << vertices[i].edg[j]->va << " vb:" << vertices[i].edg[j]->vb
			        << " flow:" << vertices[i].edg[j]->f << " capacity:" << vertices[i].edg[j]->cap;
			}
		}
		std::cout << std::endl;
	}
}

void Graph::print_resgraph()
{
    int init;
    for(int i = 0 ; i < n_vert ; i++)
    {
        std::cout << "Vértice " << i << ':' << std::endl;
        init = 0;
        for(int j = 0 ; j < vertices[i].n_edges ; j++)
        {
            if (vertices[i].edg[j]->capres != 0) {
                if(init++)
                    std::cout << " // ";
                std::cout << "va:" << vertices[i].edg[j]->va << " vb:" << vertices[i].edg[j]->vb
                          << " flow:" << vertices[i].edg[j]->capres << " capacity:" << vertices[i].edg[j]->cap;
            }
        }
        std::cout << std::endl;
    }
}

void Graph::print_edges()
{
	std::cout << "Edges:" << std::endl;
	for(int i = 0 ; i < n_edges ; i++)
	    if (!edges[i]->back)
		    std::cout << "va:" << edges[i]->va << ' ' << " vb:" << edges[i]->vb
		        << " flow:" << edges[i]->f << " capacity:" << edges[i]->cap << std::endl;
}

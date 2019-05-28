#pragma once

#include "Graph.hpp"
#include<vector>

using std::vector;

class Graph_A: public Graph
{
public:
	struct Edge
	{
		int va;
		int vb;
		double wgt;

		Edge(int i=0,int j=0,double w=0.0): va(i), vb(j), wgt(w){}
	};

	vector<Edge *> edges;

    struct Vertex
    {
        int n_edges;
        vector<Edge *> edg;

        Vertex():n_edges(0){}
    };

    vector<Vertex> vertices;

	Graph_A(int nv);

	Graph_A(const Graph_A &G2);
	
	~Graph_A();

	int add_vert();

	void add_edge(int va, int vb, double w=0.0);
};

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
		float wgt;

		Edge(int i=0,int j=0,float w=0.0): va(i), vb(j), wgt(w){}
	};

	vector<Edge *> edges;

    struct Vertex
    {
        int number;
        int n_edges;
        vector<Edge *> edg;

        Vertex(int i=0): number(i), n_edges(0){}
    };

    vector<Vertex> vertices;

	Graph_A(int nv);
	~Graph_A();

	int add_vert();
	void add_edge(int va, int vb, float w=0.0);
};

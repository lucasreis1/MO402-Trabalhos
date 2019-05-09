#pragma once

#include "graph_structs.hpp"

class Graph
{

public:
	int n_vert,n_edges;
	vector<Vertex> vertices;
	vector<Edge *> edges;

	Graph(int nver=0);

	~Graph();

	void add_vert();

	void add_edge(int va, int vb, float w=0.0);

	void print_graph();

	void print_edges();
};
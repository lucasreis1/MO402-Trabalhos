#pragma once

#include "Graph.hpp"
#include<vector>
#include <limits> //max_float

using std::vector;

class Graph_M: public Graph
{
public:
	struct Edge
	{
		bool exist;
		float w;
		Edge(): exist(false),w(std::numeric_limits<float>::max()){}
	};

	vector<vector<Edge>> edges;

	Graph_M(int nver=0);

	int add_vert();

	void add_edge(int va,int vb, float w);

	void print_edges();
};
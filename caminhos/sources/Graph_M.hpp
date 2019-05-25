#pragma once

#include "Graph.hpp"
#include<vector>
#include <limits> //max_double

using std::vector;

class Graph_M: public Graph
{
public:
	struct Edge
	{
		bool exist;
		double w;
		Edge(): exist(false),w(std::numeric_limits<double>::max()){}
	};

	vector<vector<Edge>> edges;

	Graph_M(int nver=0);

	int add_vert();

	void add_edge(int va,int vb, double w);

	void print_edges();
};
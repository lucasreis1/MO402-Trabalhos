#pragma once

#include "Graph.hpp"

typedef Graph::Edge Edge;

struct Path
{
	vector<Edge *> v;
	int n;
	Path(int nel): v(nel,nullptr), n(0){}
};

int maximum_flow(Graph &G, int s);
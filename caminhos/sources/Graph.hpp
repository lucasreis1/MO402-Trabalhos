#pragma once

class Graph
{

public:
	int n_vert;
	int n_edges;

	virtual int add_vert() = 0;

	virtual void add_edge(int va, int vb, double w) = 0;
	
	virtual ~Graph() = default;
	
protected:
	Graph(int nver=0);

};
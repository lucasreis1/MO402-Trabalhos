#pragma once

#include<vector>

using std::vector;

struct Edge
{
	int va;
	int vb;
	float wgt;

	Edge(int i=0,int j=0,float w=0.0): va(i), vb(j), wgt(w){}
};

struct Vertex
{
	int number;
	int n_edges;
	vector<Edge *> edg;

	Vertex(int i=0): number(i), n_edges(0){}
};
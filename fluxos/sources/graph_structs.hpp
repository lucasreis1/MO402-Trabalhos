#pragma once

#include<vector>

using std::vector;

struct Edge
{
	int va;
	int vb;
	int cap; // capacity
	int f; // flow
	int fres; // flow of residual graph

	int rev; // index of reversed edge
	bool blocked; // if edge is blocked true else false
	bool back; // if edge is back edge true else false

	Edge(int i=0,int j=0,int c=0,int f=0,int fr=0,int r = 0,bool b=false, bool ib=false): va(i), vb(j), cap(c), f(f), fres(fr), rev(r), blocked(b), back(ib){}
};

struct Vertex
{
	int number;
	int n_edges;
	vector<Edge *> edg;

	Vertex(int i=0): number(i), n_edges(0){}
};
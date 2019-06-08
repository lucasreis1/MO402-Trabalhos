#pragma once

#include<vector>

using std::vector;

class Graph
{

public:
	struct Edge
	{
		int va;
		int vb;
		int cap; // capacity
		int f; // flow
		int capres; // flow of residual graph

		int rev; // index of reversed edge
		bool blocked; // if edge is blocked true else false
		bool back; // if edge is back edge true else false

		Edge(int i=0,int j=0,int c=0,int f=0,int cr=0,int r = 0,bool b=false, bool ib=false): va(i), vb(j), cap(c), f(f), capres(cr), rev(r), blocked(b), back(ib){}
	};

	struct Vertex
	{
		int number;
		int n_edges;
		vector<Edge *> edg;

		Vertex(int i=0): number(i), n_edges(0){}
	};


	int n_vert,n_edges;
	vector<Vertex> vertices;
	vector<Edge *> edges;


	Graph(int nver=0);

	~Graph();

	void add_vert();

	void add_edge(int va, int vb, int cap);
};

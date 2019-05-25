#include "Bellman_Ford.hpp"
#include<limits> //max_double
#include<iostream>

using std::vector;

bool Bellman_Ford(Graph_A &G, int source, vector<int> &pred, vector<double> &d)
{
	pred.resize(G.n_vert);
	d.resize(G.n_vert);
	for(int i = 0 ; i < G.n_vert ; i++)
	{
		if(i != source)
			d[i] = std::numeric_limits<double>::max();
	}
	d[source] = 0.0;
	pred[source] = source;
	for(int k = 0 ; k < G.n_vert-1 ; k++)
	{
		for(int i = 0 ; i < G.n_edges ; i++)
		{
			int va = G.edges[i]->va;
			int vb = G.edges[i]->vb;
			if(d[va] + G.edges[i]->wgt < d[vb])
			{
				pred[vb] = va;
				d[vb] = d[va] + G.edges[i]->wgt;
			}
		}
	}
	for (int i = 0 ; i < G.n_edges ; i++) 
	{
		int va = G.edges[i]->va;
		int vb = G.edges[i]->vb;

		if(d[va] + G.edges[i]->wgt < d[vb])	
			return true;
	}
	return false;
}

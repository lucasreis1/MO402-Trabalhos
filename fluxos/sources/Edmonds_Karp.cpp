#include "Edmonds_Karp.hpp"
#include "flow_dep.hpp"
#include<queue>
#include<limits> //max_int
#include<utility> //swap

using std::queue;

bool maximal_path_bfs(Graph &G, int s,int t, Path &path, int &cp)
{
	queue<int> Q;
	vector<Edge *> pred(G.n_vert,nullptr);
	vector<int> visited(G.n_vert,0);
	int u;
	visited[s] = 1;
	Q.push(s);
	while(!Q.empty() && !visited[t])
	{
		u = Q.front();
		Q.pop();
		for(vector<Edge *>::iterator it = G.vertices[u].edg.begin() ; it < G.vertices[u].edg.end() ; ++it)
		{
			Edge *e = *it;
			int v = e->vb;
			if(!visited[v] && e->capres > 0)
			{
				Q.push(v);
				pred[v] = e;
				visited[v] = 1;
			}
		}
	}
	if(!visited[t])
		return false;
	u = t;
	int n = 0;
	cp = std::numeric_limits<int>::max();
	while(u != s)
	{
		path.v[n] = pred[u];
		cp = std::min(cp,pred[u]->capres);
		u = pred[u]->va;
		n++;
	}
	path.n = n;
	return true;
}



int edmonds_karp(Graph &G,int s,int t)
{
	int cp;
	Path path(G.n_vert);
	while(maximal_path_bfs(G,s,t,path,cp))
	{
		for(vector<Edge *>::iterator it = path.v.begin() ; it < path.v.begin() + path.n ; ++it)
		{
			Edge *e = *it;
			Edge *adir,*arev; //aresta direta (mesma direcao do grafo original) e aresta reversa (aresta contraria aquela do grafo original)
			adir = e;
			arev = G.edges[e->rev];
			if(!e->back)
				adir->f += cp;
			else
			{
				std::swap(adir,arev);
				adir->f -= cp;
			}
			adir->capres = adir->cap - adir->f;
			arev->capres = adir->f;
		}
	}
	return maximum_flow(G,s);
}
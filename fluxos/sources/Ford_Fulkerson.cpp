#include "Ford_Fulkerson.hpp"
#include "flow_dep.hpp"
#include<stack>
#include<limits> //max_int
#include<utility> //swap
#include<iostream>

using std::cout;
using std::endl;
using std::stack;


bool maximal_path_dfs(Graph &G, int s,int t, Path &path, int &cp) //DFS
{
	stack<int> S;
	vector<Edge *> pred(G.n_vert,nullptr);
	vector<int> visited(G.n_vert,0);
	int u;
	visited[s] = 1;
	S.push(s);
	while(!S.empty() && !visited[t])
	{
		u = S.top();
		S.pop();
		for(vector<Edge *>::iterator it = G.vertices[u].edg.begin() ; it < G.vertices[u].edg.end() ; ++it)
		{
			Edge *e = *it;
			int v = e->vb;
			if(!visited[v] && e->capres > 0)
			{
				S.push(v);
				pred[v] = e;
				visited[v] = 1;
			}
		}
	}
	if(!visited[t])
		return false;
	u = t;
	cp = std::numeric_limits<int>::max();
	int n = 0;
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

int ford_fulkerson(Graph &G,int s,int t)
{
	int cp;
	Path path(G.n_vert);
	while(maximal_path_dfs(G,s,t,path,cp))
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
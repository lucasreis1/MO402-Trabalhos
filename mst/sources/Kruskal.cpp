#include "Kruskal.hpp"
#include<algorithm> //sort
#include<iostream>

bool sort_function(Edge *a, Edge *b)
{
	return a->wgt < b->wgt;
}

Union_Find * create_uf_struct(int op,int size)
{
	Union_Find *uf = NULL;
	switch(op)
	{
		case 0:
		{
			uf = new Union_Find_LL(size);
			break;
		}
		case 1:
		{
			uf = new Union_Find_Tree(size);
			break;
		}
		case 2:
		{
			uf = new Union_Find_Vector(size);
			break;
		}
		default:
			std::cerr << "Opção inválida" << std::endl;
			exit(1);
	}

	return uf;
}

/*void delete_uf_struct(int op,Union_Find *uf)
{
	switch(op)
	{
		case 0:
		{
			delete (Union_Find_LL *) uf;
			break;
		}
		case 1:
		{
			delete (Union_Find_Tree *) uf;
			break;
		}
		case 2:
		{
			delete (Union_Find_Vector*) uf;
			break;
		}
	}
}*/

vector<Edge> Kruskal(Graph &G, int op, float &cost)
{
	std::cout << "inicio do sort" << std::endl;
	sort(G.edges.begin(),G.edges.end(),sort_function);
	vector<Edge> A;
	cost = 0;
	Union_Find *uf = create_uf_struct(op,G.n_vert);
	std::cout << "inicio da formacao da arvore" << std::endl;
	for(int i = 0 ; i < G.n_edges ; i++)
	{
		if(uf->find_set(G.edges[i]->va) != uf->find_set(G.edges[i]->vb))
		{
			uf->_union(G.edges[i]->va,G.edges[i]->vb);
			A.push_back(*G.edges[i]);
			cost += G.edges[i]->wgt;
		}
	}
	delete uf;
	return A;
}
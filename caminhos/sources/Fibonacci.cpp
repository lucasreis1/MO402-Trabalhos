#include "Fibonacci.hpp"
#include<limits>
#include<iostream>

Fibonacci::Fibonacci(int nel, int src): Queue(nel),min(NULL),n(0)
{
	for(int i = 0 ; i < tam ; i++)
	{
		Node *nd;
		if(i != src)
			nd = new Node(i,std::numeric_limits<float>::max());
		else
			nd = new Node(i);
		Insert_Node(nd);
	}
}

void Fibonacci::insert_node(Node *nd)
{
	if(!min || nd.chave < min.chave)
		min = nd;
	insert_on_roots(nd);
	n++;
}

int Fibonacci::extract_min()
{
	Node *z = min;
	if(!z)
	{
		std::cerr << "Impossível fazer extract_min pois heap está vazio" << std::endl;
		exit(1);
	}
	Node *tmp = Node *nd = z->filho;
	if(nd) do
	{
		nd->pai = NULL;
		nd->marca = false;
		insert_on_roots(nd);
		nd = nd->direita;
	}while(nd != tmp);

}

void Fibonacci::insert_on_roots(Node *nd)
{
	roots.push_back(nd);
	if(n)
	{
		Node *tmp = roots[n-1];
		tmp->direita = nd;
		nd->direita = roots[0];
		nd->esquerda = tmp;
		roots[0]->esquerda = nd;
	}
}

void Fibonacci::remove_from_roots(Node *nd)
{
	for(int i = 0 ; i < n && roots[i] != nd; i++)
		;
	if(n > 1)
	{
		nd->direita->esquerda = nd->esquerda;
		nd->esquerda->direita = nd->direita;
	}
	roots.erase(roots.begin(),i);
}
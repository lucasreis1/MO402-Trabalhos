#include "Fibonacci.hpp"
#include<limits> //max_float
#include<iostream>
#include<cmath> //log2
#include<utility> //swap

Fibonacci::Fibonacci(int nel, int src): Queue(nel),n(0), pos_store(tam),min(NULL)
{
	for(int i = 0 ; i < tam ; i++)
	{
		Node *nd;
		if(i != src)
			nd = new Node(i,std::numeric_limits<float>::max());
		else
			nd = new Node(i);
		pos_store[i] = nd;
		insert_node(nd);
	}
}

Fibonacci::~Fibonacci()
{
	for(unsigned int i = 0 ; i < pos_store.size() ; i++)
		delete pos_store[i];
}

void Fibonacci::insert_on_roots(Node *nd)
{
	roots.push_back(nd);
	if(n)
	{
		roots[n-1]->direita = nd;
		nd->direita = roots[0];
		nd->esquerda = roots[n-1];
		roots[0]->esquerda = nd;
	}
	n++;
}

void Fibonacci::remove_from_roots(Node *nd)
{
	int i;
	for(i = 0 ; i < n && roots[i] != nd; i++)
		;
	if(n > 1)
	{
		nd->direita->esquerda = nd->esquerda;
		nd->esquerda->direita = nd->direita;
	}
	roots.erase(roots.begin()+i);
	roots.shrink_to_fit();
	n--;
}

void Fibonacci::insert_node(Node *nd)
{
	if(!min || nd->chave < min->chave)
		min = nd;
	insert_on_roots(nd);
}

void Fibonacci::link(Node *y, Node *x)
{
	remove_from_roots(y);
	Node *pt = x->filho;
	if(pt)
	{
		pt->direita->esquerda = y;
		y->direita = pt->direita;
		y->esquerda = pt;
		pt->direita = y;
	}
	else
	{
		x->filho = y;
		y->direita = y;
		y->esquerda = y;
	}
	y->pai = x;
	x->grau++;
	y->marca = false;
}

void Fibonacci::consolidate()
{
	int D = log2(tam) + 1;
	vector<Node *> A(D,NULL);
	for(int i = 0 ; i < n ; i++)
	{
		Node *x = roots[i];
		int d = x->grau;
		while(A[d])
		{
			Node *y = A[d];
			if(x->chave > y->chave)
				std::swap(x,y);
			link(y,x);
			A[d] = NULL;
			i--;
			d++;
		}
		A[d] = x;
	}
	min = NULL;
	roots.clear();
	n = 0;
	for(int i = 0 ; i < D; i++)
	{
		if(A[i])
		{
			if(!min || A[i]->chave < min->chave)
				min = A[i];
			insert_on_roots(A[i]);
		}
	}
}

int Fibonacci::extract_min()
{
	Node *z = min;
	if(!z || !tam)
	{
		std::cerr << "Impossível fazer extract_min pois heap está vazio" << std::endl;
		exit(1);
	}
	Node *tmp, *nd;
	nd = tmp = z->filho;
	if(nd) do
	{
		Node *ptr = nd->direita;
		nd->pai = NULL;
		nd->marca = false;
		insert_on_roots(nd);
		nd = ptr;
	}while(nd != tmp);
	remove_from_roots(z);
	if(z == z->direita)
		min = NULL;
	else
	{
		min = z->direita;
		consolidate();
	}
	tam--;
	z->inq = false;
	return z->vert;
}

void Fibonacci::cut(Node *x, Node *y)
{
	if(y->filho == x)
	{
		if(x->direita == x)
			y->filho = NULL;
		else
		{
			y->filho = x->esquerda;
			x->direita->esquerda = x->esquerda;
			x->esquerda->direita = x->direita;
			x->direita = x;
			x->esquerda = x;
		}
	}
	else
	{
		x->direita->esquerda = x->esquerda;
		x->esquerda->direita = x->direita;
		x->direita = x;
		x->esquerda = x;
	}
	y->grau--;
	insert_on_roots(x);
	x->pai = NULL;
	x->marca = false;
}

void Fibonacci::cascading_cut(Node *y)
{
	Node *z = y->pai;
	if(z)
	{
		if(y->marca == false)
			y->marca = true;
		else
		{
			cut(y,z);
			cascading_cut(z);
		}
	}
}

void Fibonacci::decrease_key(int vert, float key)
{
	Node *x = pos_store[vert];
	if(key > x->chave)
	{
		std::cerr << "Impossível fazer decrease_key por tamanho de chave invalido" << std::endl;
		exit(1);
	}
	x->chave = key;
	if(x->vert != vert)
		std::cout << "??" << std::endl;
	Node *y = x->pai;
	if(y && x->chave < y->chave)
	{
		cut(x,y);
		cascading_cut(y);
	}
	if(x->chave < min->chave)
		min = x;
}

bool Fibonacci::in_queue(int vert)
{
	return pos_store[vert]->inq;
}
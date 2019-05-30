#include "Fibonacci.hpp"
#include<limits> //max_double
#include<iostream>
#include<cmath> //log2
#include<utility> //swap

#ifndef GOLDEN_LOG
#define GOLDEN_LOG 0.69424191363
#endif

Fibonacci::Fibonacci(int nel, int src): Queue(nel),n(0), pos_store(tam),min(NULL)
{
	int t = log(tam)/0.20898764 + 1;
	A.resize(t);
	for(int i = 0 ; i < tam ; i++)
	{
		Node *nd;
		if(i != src)
			nd = new Node(i,std::numeric_limits<double>::infinity());
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
	if(n)
	{
		min->direita->esquerda = nd;
		nd->direita = min->direita;
		nd->esquerda = min;
		min->direita = nd;
	}
	else
		nd->esquerda = nd->direita = nd;
	n++;
}

void Fibonacci::remove_from_roots(Node *nd)
{
	if(n > 1)
	{
		nd->direita->esquerda = nd->esquerda;
		nd->esquerda->direita = nd->direita;
	}
	n--;
}

void Fibonacci::insert_node(Node *nd)
{
	insert_on_roots(nd);
	if(!min || nd->chave < min->chave)
		min = nd;
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
		y->direita = y->esquerda = y;
	}
	y->pai = x;
	x->grau++;
	y->marca = false;
}

void Fibonacci::consolidate()
{
	int D = log2(tam)/GOLDEN_LOG + 1;
	for(int i = 0 ; i < D ; i++)
		A[i] = NULL;
	Node *next, *ptr;
	next = min->direita;
	do
	{
		Node *x = ptr = next;
		next = next->direita;
		int d = x->grau;
		while(A[d])
		{
			Node *y = A[d];
			if(x->chave > y->chave)
				std::swap(x,y);
			link(y,x);
			A[d] = NULL;
			d++;
		}
		A[d] = x;
	}while(ptr != min);
	min = NULL;
	n = 0;
	for(int i = 0 ; i < D; i++)
		if(A[i])
		{
			insert_on_roots(A[i]);
			if(!min || A[i]->chave < min->chave)
				min = A[i];
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

void Fibonacci::cut(Node *x, Node *y) // x = filho, y = pai
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
		}
	}
	else
	{
		x->direita->esquerda = x->esquerda;
		x->esquerda->direita = x->direita;
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

void Fibonacci::decrease_key(int vert, double key)
{
	Node *x = pos_store[vert];
	if(key > x->chave)
	{
		std::cerr << "Impossível fazer decrease_key por tamanho de chave invalido" << std::endl;
		exit(1);
	}
	x->chave = key;
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
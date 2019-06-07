#include "Heap.hpp"
#include<iostream>
#include<limits> //max_float
#include<utility> //swap

Heap::Heap(int nel,int src): Queue(nel), H(tam), pos_store(tam)
{
	build_heap(src);
}

Heap::~Heap()
{
	for(unsigned int i = 0 ; i < H.size() ; i++)
		delete H[i];
}

void Heap::swp(int i, int j)
{
	swap(H[i],H[j]);
	swap(H[i]->pos,H[j]->pos);
}

int Heap::parent(int i)
{
	return (i-1)/2;
}

int Heap::left(int i)
{
	return 2*i+1;
}

int Heap::right(int i)
{
	return 2*i+2;
}

void Heap::heapify(int i)
{
	int l,r;
	int smallest;
	l = left(i);
	r = right(i);
	smallest = i;
	if(l < tam && H[l]->val < H[smallest]->val)
		smallest = l;
	if(r < tam && H[r]->val < H[smallest]->val)
		smallest = r;
	if(i != smallest)
	{
		swp(i,smallest);
		heapify(smallest);
	}
}

void Heap::build_heap(int src)
{
	H[src] = new Node();
	H[src]->pos = src;
	H[src]->vert = src;
	H[src]->val = 0.0;
	pos_store[src] = H[src];
	for(int i = 0 ; i < tam ; i++)
	{
		if(i != src)
		{
			H[i] = new Node();
			H[i]->pos = i;
			H[i]->vert = i;
			H[i]->val = std::numeric_limits<float>::infinity();
			pos_store[i] = H[i];
		}
	}

	for(int i = tam/2-1 ; i >= 0 ; i--)
		heapify(i);
}

int Heap::extract_min()
{
	if(tam < 1)
	{
		std::cerr << "Erro no tamanho do heap" << std::endl;
		exit(1);
	}
	int min;
	min = H[0]->vert;
	swp(0,tam-1);
	tam--;
	heapify(0);
	return min;
}

void Heap::decrease_key(int vert, float key)
	{
		int pos = pos_store[vert]->pos;
		if(H[pos]->val < key)
		{
			std::cerr << "Tamanho inválido para decrease_key" << std::endl;
			exit(1);
		}
		H[pos]->val = key;
		int p = parent(pos);
		while(pos > 0 && H[pos]->val < H[p]->val)
		{
			swp(pos,p);
			pos = p;
			p = parent(pos);
		}
	}

//se ainda esta na fila
bool Heap::in_queue(int vert)
{
	return pos_store[vert]->pos < tam;
}

float Heap::get_value(int vert)
{
	return pos_store[vert]->val;
}

#pragma once

class Queue
{
public:
	int tam;
	//virtual void build_heap(int src) = 0;
	virtual int extract_min() = 0;
	virtual void decrease_key(int vert,float key) = 0;
	virtual bool in_queue(int vert) = 0; //Retorna true caso o elemento esteja dentro da queue, false caso não
	virtual float get_value(int vert) = 0; //Retorna o valor do elemento vert na queue

	Queue(int n = 0);
	virtual ~Queue() = default;
};

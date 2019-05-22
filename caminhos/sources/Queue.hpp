#pragma once

class Queue
{
public:
	int tam;
	
	virtual int extract_min() = 0;
	
	virtual void decrease_key(int vert,float key) = 0;
	
	virtual bool in_queue(int vert) = 0; //Retorna true caso o elemento esteja dentro da queue, false caso não

	virtual ~Queue() = default;
protected:
	Queue(int n = 0);
};

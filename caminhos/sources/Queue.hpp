#pragma once

class Queue
{
public:
	int tam;
	
	virtual int extract_min() = 0;
	
	virtual void decrease_key(int vert,double key) = 0;

	virtual ~Queue() = default;
protected:
	Queue(int n = 0);
};

#include <cstddef>
#pragma once

class Union_Find
{
public:
	virtual void make_set(int x) = 0;
	virtual int find_set(int x) = 0;
	virtual void _union(int x,int y) = 0;
	virtual void link(int x,int y) = 0;

	int n_el;

	Union_Find(int nel=0);
	virtual ~Union_Find();
};

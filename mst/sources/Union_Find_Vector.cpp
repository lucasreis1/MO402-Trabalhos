#include "Union_Find_Vector.hpp"

Union_Find_Vector::Union_Find_Vector(int nel): Union_Find(nel), nodes(nel)
{
	for(int i = 0 ; i < n_el ; i++)
	{
		make_set(i);
	}
}

void Union_Find_Vector::make_set(int x)
{
	nodes[x].parent = x;
}

int Union_Find_Vector::find_set(int x)
{
	return nodes[x].parent;
}

void Union_Find_Vector::_union(int x,int y)
{
	link(find_set(x),find_set(y));
}

void Union_Find_Vector::link(int x,int y)
{
	for(int i = 0 ; i < n_el; i++)
	{
		if(nodes[i].parent == y)
			nodes[i].parent = x;
	}
}
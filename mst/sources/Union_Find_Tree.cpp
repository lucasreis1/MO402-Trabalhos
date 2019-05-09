#include "Union_Find_Tree.hpp"

Union_Find_Tree::Union_Find_Tree(int nel): Union_Find(nel), nodes(nel)
{
	for(int i = 0 ; i < n_el ; i++)
	{
		make_set(i);
	}
}

void Union_Find_Tree::make_set(int x)
{
	nodes[x].parent = x;
}

int Union_Find_Tree::find_set(int x)
{
	if(nodes[x].parent != x)
		nodes[x].parent = find_set(nodes[x].parent);
	return nodes[x].parent;
}

void Union_Find_Tree::_union(int x, int y)
{
	link(find_set(x),find_set(y));
}

void Union_Find_Tree::link(int x,int y)
{
	if(nodes[x].size > nodes[y].size)
		nodes[y].parent = x;
	else
	{
		nodes[x].parent = y;
		if(nodes[x].size == nodes[y].size)
			nodes[y].size += 1;
	}
}
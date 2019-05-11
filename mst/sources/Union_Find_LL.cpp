#include "Union_Find_LL.hpp"

Union_Find_LL::Union_Find_LL(int nel): Union_Find(nel), nodes(n_el)
{
	for(int i = 0 ; i < n_el ; i++)
	{
		make_set(i);
	}
}

Union_Find_LL::~Union_Find_LL()
{
	for(unsigned int i = 0 ; i < components.size() ; i++)
		delete components[i];
}

void Union_Find_LL::make_set(int i)
{
	nodes[i].index = i;
	Node *ptr = new Node(i);
	ptr->head = &nodes[i];
	ptr->tail = &nodes[i];
	nodes[i].head = ptr;
	components.push_back(ptr);
}

int Union_Find_LL::find_set(int x)
{
	return nodes[x].head->index;
}

void Union_Find_LL::_union(int x, int y)
{
	link(find_set(x),find_set(y));
}

void Union_Find_LL::link(int x, int y)
{
	components[x]->tail->tail = components[y]->head;
	components[x]->tail = components[y]->tail;
	Node *ptr = components[y]->head;
	while(ptr)
	{
		ptr->head = components[x];
		ptr = ptr->tail;
	}
}
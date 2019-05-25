#include "Queue.hpp"
#include<vector>

using std::vector;
using std::swap;

class Heap: public Queue
{
private:

	struct Node
	{
		int pos;
		int vert;
		double val;
	};

	vector<Node *> H;
	vector<Node *> pos_store;

public:
	Heap(int nel,int src = 0);

	~Heap();

	void swp(int i, int j);

	int parent(int i);

	int left(int i);

	int right(int i);

	void heapify(int i);

	void build_heap();

	int extract_min();

	void decrease_key(int vert, double key);

	bool in_queue(int vert);

	double get_value(int vert);
};
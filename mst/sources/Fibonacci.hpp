#include<vector>
#include "Queue.hpp"

using std::vector;
//using std::swap;

using namespace std;

struct Node
{
	float chave;
	int grau, vert;
	Node *pai, *filho, *esquerdo, *direito;
	bool marca;
};

class Fibonacci: public Queue
{
private:

	int n;
	Node *min;
	vector<Node *> roots;

	Fibonacci* make_fib_heap();

	vector<Node *> pos_store;

public:
	Fibonacci(int size, int src);

	void build_heap(int src);

	void update_min(Fibonacci *H, Node *x);

	void fib_join_root(Node *x);

	void fib_remove_root(Node *x);

	void fib_insert(Fibonacci *H, Node *x);

	Node* get_min();

	Fibonacci* fib_union(Fibonacci *H1, Fibonacci *H2);

	int extract_min();

	void consolidate(Fibonacci *H);

	void fib_heap_link(Fibonacci *H, Node *y, Node *x);

	void cascading_cut(Fibonacci *H, Node *y);

	void cut(Fibonacci *H, Node *x, Node *y);

	void decrease_key(int vert, float k);

	//void fib_heap_delete(int vert);

	float get_value(int vert);

	bool in_queue(int vert);
};
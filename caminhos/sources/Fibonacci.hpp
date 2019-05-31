#include "Queue.hpp"
#include<vector>

using std::vector;

class Fibonacci: public Queue
{
private:
	struct Node
	{
		Node *pai;
		Node *filho;
		Node *esquerda,*direita;
		int grau;
		int vert;
		double chave;
		bool marca;
		bool inq;
		Node(int v,double k=0.0):pai(nullptr),filho(nullptr),esquerda(this),direita(this),grau(0),vert(v),chave(k),marca(false),inq(true){}
	};

	int n;
	vector<Node *> roots;
	vector<Node *> pos_store;
	vector<Node *> A;
	Node *min;
public:
	Fibonacci(int nel,int src);

	~Fibonacci();

	void insert_on_roots(Node *nd);

	void remove_from_roots(Node *nd);

	void insert_node(Node *nd);

	void link(Node *y, Node *x);

	void consolidate();

	int extract_min();

	void cut(Node *x, Node *y);

	void cascading_cut(Node *y);

	void decrease_key(int vert,double key);

	bool in_queue(int vert);

	void print_roots();
};
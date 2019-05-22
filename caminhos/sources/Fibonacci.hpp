#include "Queue.hpp"

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
		float chave;
		bool marca;
		bool inq;
		Node(int v,float k=0.0):pai(NULL),filho(NULL),esquerda(this),direita(this),grau(0),marca(false),inq(true),vert(v),chave(k){}
	}

	int n;
	vector<Node *> roots;
	vector<Node *> pos_store;
	Node *min;
public:
	void Fibonacci(int nel,int src);

	void ~Fibonacci();

	void insert_on_roots(Node *nd);

	void remove_from_roots(Node *nd);

	void Insert_Node(Node *nd);

	void link(Node *y, Node *x);

	void consolidate();

	void extract_min();

	void cut(Node *x, Node *y);

	void cascading_cut(Node *y);

	void decrease_key(int vert,float key);

	void in_queue(int vert);
}
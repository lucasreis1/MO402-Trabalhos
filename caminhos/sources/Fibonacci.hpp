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
		Node(int v,float k=0.0):pai(NULL),filho(NULL),esquerda(this),direita(this),grau(0),marca(false),vert(v),chave(k){}
	}

	int n;
	vector<Node *> roots;
	Node *min;
public:
	void Fibonacci(int nel,int src);

	void Insert_Node(Node *nd);
}
#include "Fibonacci.hpp"

Fibonacci::Fibonacci(int size, int src)
{
	set_size(size);
	build_heap(src);
}

void Fibonacci::set_size(int i)
{
	this->size = i;
}


void Fibonacci::build_heap(int src)
{
	int i;

	if(this->size)
	{
		Node *x = new Node();

		this->min = x;
		this->n = 1;

		x->chave = 0.0;
		x->vert = src;

		pos_store[src] = x;

		fib_insert(this, x);

		for(i = 0 ; i < this->size ; i++)
		{
			if(i != src)
			{
				x = new Node();

				x->chave = std::numeric_limits<float>::max();;

				fib_insert(this, x);

				pos_store[i] = x;
			}
		}
	}
}

void Fibonacci::update_min(Fibonacci *H, Node *x)
{
	if(!(H->min) || x->chave < (H->min)->chave)
	{
		H->min = x;
		H->n = H->n + 1;
	}
}
///////////////////////////////////////////////////////////////////////
void Fibonacci::fib_join_root(Node *x, Fibonacci *H)
{
	(this->roots).insert(this->roots.end(), x);
}

void Fibonacci::fib_remove_root(Node *x, Fibonacci *H)
{
	uint i;

	for(i = 0; i < (H->roots).size() && (H->roots)[i] != x; i++) ;

	(H->roots).erase((H->roots).begin()+i);
}

void Fibonacci::fib_insert(Fibonacci *H, Node *x)
{

	x->grau = 0;
	x->pai = NULL;
	x->filho = NULL;
	x->marca = false;
	x->esquerdo = x;
	x->direito = x;

	fib_join_root(x, H);

	update_min(H, x);
}

Node* Fibonacci::get_min()
{
	return this->min;
}

Fibonacci* Fibonacci::fib_union(Fibonacci *H1, Fibonacci *H2)
{
	//Fibonacci *H = Fibonacci((H1->roots).size() + (H2->roots).size(), H1->min);

	this->min = H1->min;
	(this->roots).reserve((H1->roots).size() + (H2->roots).size());
	(this->roots).insert( (this->roots).end(), (H1->roots).begin(), (H1->roots).end() );
	(this->roots).insert( (this->roots).end(), (H2->roots).begin(), (H2->roots).end() );

	if(!(H1->min) || ((H2->min) && (H1->min) > (H2->min)))
		this->min = H2->min;

	this->n = H1->n + H2->n;
	free(H1);
	free(H2);

	return this;
}

int Fibonacci::extract_min()
{
	Node *z = get_min();
	Node *aux;

	int i;

	if(z)
	{
		pos_store[z->vert] = NULL;

		for(aux = z->filho; aux->direito != z->filho; aux = aux->direito)
		{
			fib_join_root(aux, this);
			aux->pai = NULL;
		}
		fib_join_root(aux, this);
		aux->pai = NULL;

		for(i = 0; this->roots[i] != z ;i++) ;

		(this->roots).erase((this->roots).begin() + i);

		if(z == z->direito)
			this->min = NULL;
		else
		{
			this->min = z->direito;
			consolidate(this);
		}
		this->n--;
	}

	return z->vert;
}

void Fibonacci::consolidate(Fibonacci *H)
{
	vector<Node *> A;
	uint i, d;
	Node *x, *y;

	for(i = 0; i < log(H->n) ; i++)
		A.insert(A.end(), NULL);

	for(i = 0; i < (H->roots).size(); i++)
	{
		x = (H->roots)[i];
		d = x->grau;

		while(A[d])
		{
			y = A[d];
			if(x->chave > y->chave)
				swap(x, y);
			fib_heap_link(H, y, x);
			A[d] = NULL;
			d++;
		}
		A[d] = x;
	}

	H->min = NULL;

	for(i = 0; i < log(H->n) ;i++)
	{
		if(A[i])
		{
			fib_join_root(A[i], H);
			if(!(H->min) || A[i]->chave < (H->min)->chave)
				H->min = A[i];
		}
	}
}

void Fibonacci::fib_heap_link(Fibonacci *H, Node *y, Node *x)
{
	fib_remove_root(y, H);

	y->pai = x;
	y->direito = x->filho;
	y->esquerdo = x->filho->esquerdo;
	x->filho = y;
	x->grau++;

	y->marca = false;
}

void Fibonacci::decrease_key(int vert, float k)
{
	Node *y;
	Node *x = this->pos_store[vert];

	if(k > x->chave)
	{
		std::cerr << "Nova chave maior que a atual" << std::endl;
        exit(1);
	}

	x->chave = k;
	y = x->pai;

	if(y && x->chave < y->chave)
	{
		cut(this, x, y);
		cascading_cut(this, y);
	}

	if(x->chave < (this->min)->chave)
		this->min = x;
}

void Fibonacci::cut(Fibonacci *H, Node *x, Node *y)
{
	Node *aux;

	for(aux = y->filho; aux != x; aux = aux->direito) ;

	aux->direito->esquerdo = aux->esquerdo;
	aux->esquerdo->direito = aux->direito;

	y->grau--;

	fib_join_root(x, H);

	x->pai = NULL;
	x->marca = false;
}

void Fibonacci::cascading_cut(Fibonacci *H, Node *y)
{
	Node *z = y->pai;

	if(z)
	{
		if(y->marca == false)
			y->marca = true;
		else
		{
			cut(H, y, z);
			cascading_cut(H, z);
		}
	}
}

/*void Fibonacci::fib_heap_delete(int vert)
{
	pos_store[vert] = NULL;
	decrease_key(vert, -1*std::numeric_limits<float>::max());
	extract_min();
}*/

bool Fibonacci::in_queue(int vert)
{
	if(pos_store[vert])
		return true;

	return false;
}

float Fibonacci::get_value(int vert)
{
	return pos_store[vert]->chave;
}
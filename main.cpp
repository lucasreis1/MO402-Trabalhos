#include<iostream>
#include<vector>
#include<algorithm> //sort
#include<utility> //swap
#include<fstream>
#include<limits> //max_float

using namespace std;



class Union_Find
{
public:
	virtual void make_set(int x) = 0;
	virtual int find_set(int x) = 0;
	virtual void _union(int x,int y) = 0;
	virtual void link(int x,int y) = 0;

	int n_el;

	Union_Find(int nel=0): n_el(nel){}
};

class Union_Find_Vector: public Union_Find
{
	private:
		struct Node
		{
			int parent;
			int size;
			Node(int p = 0): parent(p),size(1){}
		};

	vector<Node> nodes;

	public:
		Union_Find_Vector(int nel=0): Union_Find(nel), nodes(nel)
		{
			for(int i = 0 ; i < n_el ; i++)
			{
				make_set(i);
			}
		}

		void make_set(int x)
		{
			nodes[x].parent = x;
		}

		int find_set(int x)
		{
			return nodes[x].parent;
		}

		void _union(int x,int y)
		{
			link(find_set(x),find_set(y));
		}

		void link(int x,int y)
		{
			int t;
			if(nodes[x].size >= nodes[y].size)
			{
				t = nodes[y].size;
				nodes[x].size += nodes[y].size;
				for(int i = 0 ; i < n_el && t ; i++)
				{
					if(nodes[i].parent == y)
					{
						nodes[i].parent = x;
						t--;
					}
				}
			}
			else
			{
				t = nodes[x].size;
				nodes[y].size += nodes[x].size;
				for(int i = 0 ; i < n_el && t ; i++)
				{
					if(nodes[i].parent == x)
					{
						nodes[i].parent = y;
						t--;
					}
				}
			}
		}
};

class Union_Find_LL: public Union_Find
{

	private:
		struct Node
		{
			Node *head;
			Node *tail;
			int index;
			int size;

			Node(int n=1): head(this),tail(NULL), index(n), size(1){}
		};

		vector<Node> nodes;
		vector<Node *> components;

	public:
		Union_Find_LL(int nel= 0): Union_Find(nel), nodes(n_el)
		{
			for(int i = 0 ; i < n_el ; i++)
			{
				make_set(i);
			}
		}

		~Union_Find_LL()
		{
			for(int i = 0 ; i < components.size() ; i++)
				delete components[i];
		}

		void make_set(int i)
		{
			nodes[i].index = i;
			Node *ptr = new Node(i);
			ptr->head = &nodes[i];
			ptr->tail = &nodes[i];
			nodes[i].head = ptr;
			components.push_back(ptr);
		}

		int find_set(int x)
		{
			return nodes[x].head->index;
		}

		void _union(int x, int y)
		{
			link(find_set(x),find_set(y));
		}

		void link(int x, int y)
		{
			if(components[x]->size >= components[y]->size)
			{
				components[x]->size += components[y]->size;
				components[x]->tail->tail = components[y]->head;
				components[x]->tail = components[y]->tail;
				Node *ptr = components[y]->head;
				while(ptr)
				{
					ptr->head = components[x];
					ptr = ptr->tail;
				}
			}
			else
			{
				components[y]->size += components[x]->size;
				components[y]->tail->tail = components[x]->head;
				components[y]->tail = components[x]->tail;
				Node *ptr = components[x]->head;
				while(ptr)
				{
					ptr->head = components[y];
					ptr = ptr->tail;
				}
			}
		}

		void print_parents()
		{
			//TODO
		}
};

class Union_Find_Tree: public Union_Find
{

private:
	struct Node
	{
		int parent;
		int size;
		Node(int p=0): parent(p),size(1) {}
	};

	vector<Node> nodes;

public:
	Union_Find_Tree(int nel=0): Union_Find(nel), nodes(nel)
	{
		for(int i = 0 ; i < n_el ; i++)
		{
			make_set(i);
		}
	}

	void make_set(int x)
	{
		nodes[x].parent = x;
	}

	int find_set(int x)
	{
		if(nodes[x].parent != x)
			nodes[x].parent = find_set(nodes[x].parent);
		return nodes[x].parent;
	}

	void _union(int x, int y)
	{
		link(find_set(x),find_set(y));
	}

	void link(int x,int y)
	{
		if(nodes[x].size >= nodes[y].size)
		{
			nodes[y].parent = x;
			nodes[x].size += nodes[y].size;
		}
		else
		{
			nodes[x].parent = y;
			nodes[y].size += nodes[x].size;
		}
	}

	void print_parents()
	{
		for(int i = 0 ; i < n_el ; i++)
		{
			cout << "Node:" << i << "//Parent: " << find_set(i) << endl;
		}
	}
};

class Queue
{
public:
	int tam;
	virtual void build_heap(int src) = 0;
	virtual int extract_min() = 0;
	virtual void decrease_key(int pos,float key) = 0;
	virtual bool in_queue(int pos) = 0;

	Queue(int n = 0): tam(n){}
};

class Heap: public Queue
{
private:

	struct Node
	{
		int pos;
		float val;
	};

	vector<Node> H;
	vector<int> pos_holder;

public:
	Heap(int nel,int src = 0): Queue(nel), H(tam), pos_holder(tam)
	{
		build_heap(src);
	}

	void swp(int i, int j)
	{
		swap(H[i],H[j]);
		swap(pos_holder[i],pos_holder[j]);
	}

	int parent(int i)
	{
		return (i-1)/2;
	}

	int left(int i)
	{
		return 2*i+1;
	}

	int right(int i)
	{
		return 2*i+2;
	}

	void heapify(int i)
	{
		int l,r;
		int smallest;
		l = left(i);
		r = right(i);
		smallest = i;
		if(l < tam && H[l].val < H[smallest].val)
			smallest = l;
		if(r < tam && H[r].val < H[smallest].val)
			smallest = r;
		if(i != smallest)
		{
			swp(i,smallest);
			heapify(smallest);
		}
	}

	void build_heap(int src)
	{
		H[src].pos = src;
		H[src].val = 0;
		pos_holder[src] = src;
		for(int i = 0 ; i < tam ; i++)
		{
			if(i != src)
			{
				pos_holder[i] = i;
				H[i].pos = i;
				H[i].val = numeric_limits<float>::max();
			}
		}

		for(int i = tam/2-1 ; i >= 0 ; i--)
			heapify(i);
	}

	int extract_min()
	{
		if(tam < 1)
		{
			cerr << "Erro no tamanho do heap" << endl;
			exit(1);
		}
		int min;
		min = H[0].pos;
		swp(0,tam-1);
		tam--;
		heapify(0);
		cout << "- # - # -" << endl;
		cout << "min = " << min << "//new_min = pos:" << H[0].pos << " val:" << H[0].val << endl;
		return min;
	}

	void decrease_key(int pos, float key)
	{
		int h_pos = pos_holder[pos];
		if(H[h_pos].val < key)
		{
			cerr << "Tamanho inválido para decrease_key" << endl;
			exit(1);
		}

		H[h_pos].val = key;

		while(h_pos > 0 && H[h_pos].val < H[parent(h_pos)].val)
		{
			swp(h_pos,parent(h_pos));
			h_pos = parent(h_pos);
		}
	}

	bool in_queue(int pos)
	{
		return H[pos_holder[pos]].pos < tam;
	}

	float get_value(int pos)
	{
		return H[pos_holder[pos]].val;
	}
};

struct Edge
{
	int va;
	int vb;
	float wgt;

	Edge(int i=0,int j=0,float w=0.0): va(i), vb(j), wgt(w){}
};

struct Vertex
{
	int number;
	int n_edges;
	vector<Edge *> edg;

	Vertex(int i=0): number(i), n_edges(0){}
};

class Graph
{

public:
	int n_vert,n_edges;
	vector<Vertex> vertices;
	vector<Edge *> edges;
	Graph(int nver=0): n_vert(nver), vertices(nver), n_edges(0)
	{
		for(int i = 0 ; i < n_vert ; i++)
			vertices[i].number = i;
	}

	~Graph()
	{
		for(int i = 0 ; i < n_edges ; i++)
			delete edges[i];
	}

	void add_vert()
	{
		vertices.resize(++n_vert,Vertex(n_vert-1));
	}

	void add_edge(int va, int vb, float w=0.0)
	{
		if(va < n_vert && vb < n_vert)
		{
			Edge *new_e = new Edge(va,vb,w);
			edges.push_back(new_e);
			n_edges++;
			vertices[va].edg.push_back(new_e);
			vertices[vb].edg.push_back(new_e);
			vertices[va].n_edges++;
			vertices[vb].n_edges++;
		}
		else
		{
			cerr << "Vértice inexistente" << endl;
			exit(1);
		}
	}


	
	void print_graph()
	{
		for(int i = 0 ; i < n_vert ; i++)
		{
			cout << "Vértice " << i << ':' << endl;
			for(int j = 0 ; j < vertices[i].n_edges; j++)
			{
				if(j)
					cout << " // ";
				cout << "va:" << vertices[i].edg[j]->va << " vb:" << vertices[i].edg[j]->vb << " weight:" << vertices[i].edg[j]->wgt;
			}
			cout << endl;
		}
	}

	void print_edges()
	{
		cout << "Edges:" << endl;
		for(int i = 0 ; i < n_edges ; i++)
			cout << "va:" << edges[i]->va << ' ' << " vb:" << edges[i]->vb << " weight:" << edges[i]->wgt<< endl;
	}
};

static bool sort_function(Edge *a, Edge *b)
{
	return a->wgt < b->wgt;
}

Union_Find * create_uf_struct(int op,int size)
{
	Union_Find *uf = NULL;
	switch(op)
	{
		case 0:
		{
			uf = new Union_Find_LL(size);
			break;
		}
		case 1:
		{
			uf = new Union_Find_Tree(size);
			break;
		}
		case 2:
		{
			uf = new Union_Find_Vector(size);
			break;
		}
		default:
			cerr << "Opção inválida" << endl;
			exit(1);
	}

	return uf;
}

void delete_uf_struct(int op,Union_Find *uf)
{
	switch(op)
	{
		case 0:
		{
			delete (Union_Find_LL *) uf;
			break;
		}
		case 1:
		{
			delete (Union_Find_Tree *) uf;
			break;
		}
		case 2:
		{
			delete (Union_Find_Vector*) uf;
			break;
		}
	}
}

vector<Edge> Kruskal(Graph &G, int op, float &cost)
{
	cout << "inicio do sort" << endl;
	sort(G.edges.begin(),G.edges.end(),sort_function);
	vector<Edge> A;
	cost = 0;
	Union_Find *uf = create_uf_struct(op,G.n_vert);
	cout << "inicio da formacao da arvore" << endl;
	for(int i = 0 ; i < G.n_edges ; i++)
	{
		if(uf->find_set(G.edges[i]->va) != uf->find_set(G.edges[i]->vb))
		{
			uf->_union(G.edges[i]->va,G.edges[i]->vb);
			A.push_back(*G.edges[i]);
			cost += G.edges[i]->wgt;
		}
	}
	delete_uf_struct(op,uf);
	return A;
}

vector<Edge> Prim(Graph G, int op, float &cost, int src=0)
{
	vector<Edge> A;
	vector<Edge> Pi(G.n_vert);
	cost = 0;
	Heap Hp(G.n_vert,src);
	while(Hp.tam > 0)
	{
		int u = Hp.extract_min();
		vector<Edge *> adj = G.vertices[u].edg;
		int nadj = G.vertices[u].n_edges;
		for(int i = 0 ; i < nadj ; i++)
		{
			int viz = (adj[i]->va == u?adj[i]->vb:adj[i]->va);
			if(Hp.in_queue(viz) && adj[i]->wgt < Hp.get_value(viz))
			{
				Hp.decrease_key(viz,adj[i]->wgt);
				Pi[viz] = *adj[i];
			}
		}
		if(u != src)
		{
			cout << Pi[u].va << ' ' << Pi[u].vb << ' ' << Pi[u].wgt << endl;
			A.push_back(Pi[u]);
			cost += Pi[u].wgt;
		}
	}
	return A;
}

int main(int argc, char * argv[])
{
	if(argc < 5)
	{
		cerr << "Uso: ./main <Alg> <x> <arq_in> <arq_out>" << endl;
		return 1;
	}
	fstream infile,outfile;
	int nver,narestas,va,vb;
	float w,cost;
	bool works = true;
	vector<Edge> res;
	infile.open(argv[3]);
	if(!infile.is_open())
	{
		cerr << "Problema na arbetura do arquivo de entrada!" << endl;
		return 1;
	}
	cout << "inicio da construcao do grafo" << endl;
	infile >> nver >> narestas;
	Graph G(nver);
	for(int i = 0 ; i < narestas ; i++)
	{
		infile >> va >> vb >> w;
		G.add_edge(va,vb,w);
	}
	infile.close();
	cout << "inicio do algoritmo" << endl;

	int op = argv[2][0] - '0';
	if(string(argv[1]) == "Kruskal")
		res = Kruskal(G,op,cost);
	else if(string(argv[1]) == "Prim")
		res = Prim(G,op,cost);
	outfile.open(argv[4],fstream::out);
	outfile << cost << endl;
	for(int i = 0 ; i < res.size() ; i++)
		outfile << res[i].va << ' ' << res[i].vb << ' ' << res[i].wgt << endl;
	outfile.close();
	return 0;
}
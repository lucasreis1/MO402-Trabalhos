#include "Graph.hpp"
#include<vector>

using std::vector;

class Graph_M: public Graph
{
private:
	struct Edge
	{
		bool exist;
		float w;
		Edge(): exist(false),w(0.0){}
	};

	vector<vector<Edge>> edges;
public:
	Graph_M(int nver=0);

	int add_vert();

	void add_edge(int va,int vb, float w);

	void print_edges();
};
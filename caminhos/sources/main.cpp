#include "Graph.hpp"
#include "Graph_A.hpp" //Lista de adjacencias
#include "Graph_M.hpp" //Matriz de adjacencias

using namespace std;

int main()
{
	Graph_M G(4);
	G.add_edge(0,1,2.5);
	G.add_edge(0,3,5.72);
	G.add_edge(2,1,3.14);
	G.print_edges();
	return 0;
}
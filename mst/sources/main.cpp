#include "Kruskal.hpp"
#include "Prim.hpp"
#include "Graph.hpp"
#include<iostream>
#include<fstream>

using namespace std;

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
	outfile << cost;
	for(unsigned int i = 0 ; i < res.size() ; i++)
		outfile << endl << res[i].va << ' ' << res[i].vb << ' ' << res[i].wgt;
	outfile.close();
	return 0;
}
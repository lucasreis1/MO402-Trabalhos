#include "Graph_A.hpp" //Lista de adjacencias
#include "Graph_M.hpp" //Matriz de adjacencias
#include "Bellman_Ford.hpp"
#include<vector>
#include<iostream>
#include<fstream> //leitura e escrita de arquivos

using namespace std;

void print_path(vector<int> pred, int vert, int source)
{
	if(vert == source)
		cout << source;
	else
	{
		print_path(pred,pred[vert],source);
		cout << ' ' << vert;
	}
}

int main(int argc, char * argv[])
{
	/*if(argc < 5)
	{
		cerr << "Uso: ./main <bellman-ford/dijkstra/floyd-warshall/johnson> <x> <arq-in> <arq-out>" << endl;
		return 1;
	}*/

	fstream infile,outfile;
	int nver,narestas,source,va,vb;
	float peso;

	infile.open(argv[1]);
	if(!infile.is_open())
	{
		cerr << "Problema na abertura do arquivo de entrada!" << endl;
		return 1;
	}

	cout << "Lendo grafo..." << endl;
	infile >> nver >> narestas >> source;
	Graph_A G(nver);
	for(int i = 0 ; i < narestas; i++)
	{
		infile >> va >> vb >> peso;
		G.add_edge(va,vb,peso);
	}
	infile.close();
	vector<double> costs;
	vector<int> pred = Bellman_Ford(G,source,costs);
	for(int i = 0 ; i < G.n_vert ; i++)
	{
		cout << i << ": ";
		print_path(pred,i,source);
		cout << endl;
	}
	return 0;
}
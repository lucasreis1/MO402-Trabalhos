#include "Kruskal.hpp"
#include "Prim.hpp"
#include "Graph.hpp"
#include<chrono> //medir tempo
#include<iostream>
#include<fstream> //leitura de arquivos
#include<algorithm>

using namespace std;

int main(int argc, char * argv[])
{
	if(argc < 5)
	{
		cerr << "Uso: ./main <kruskal/prim> <x> <arq-in> <arq-out>" << endl;
		return 1;
	}
	fstream infile,outfile;
	int nver,narestas,va,vb;
	float w;
	double cost;
	vector<Edge> res;
	infile.open(argv[3]);
	if(!infile.is_open())
	{
		cerr << "Problema na abertura do arquivo de entrada!" << endl;
		return 1;
	}
	cout << "Lendo grafo..." << endl;
	infile >> nver >> narestas;
	Graph G(nver);
	for(int i = 0 ; i < narestas ; i++)
	{
		infile >> va >> vb >> w;
		G.add_edge(va,vb,w);
	}
	infile.close();
	int op = argv[2][0] - '0';
	chrono::system_clock::time_point start,end;
	cout << "Iniciando algoritmo..." << endl;
	if(string(argv[1]) == "kruskal")
	{
		start = chrono::system_clock::now();
		res = Kruskal(G,op,cost);
		end = chrono::system_clock::now();
	}
	else if(string(argv[1]) == "prim")
	{
		start = chrono::system_clock::now();
		res = Prim(G,op,cost);
		end = chrono::system_clock::now();
	}
	else
	{
		cerr << "Opção inválida" << endl;
		return 1;
	}
	chrono::milliseconds elapsed = chrono::duration_cast<chrono::milliseconds>(end-start);
	cout << "Tempo de execução do algoritmo: " << elapsed.count() << " ms" << endl;
	outfile.open(argv[4],fstream::out);
	outfile << fixed << cost;
	for(unsigned int i = 0 ; i < res.size() ; i++)
		outfile << endl << fixed << res[i].va << ' ' << res[i].vb << ' ' << res[i].wgt;
	outfile.close();
	return 0;
}

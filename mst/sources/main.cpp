#include "Kruskal.hpp"
#include "Prim.hpp"
#include "Graph.hpp"
#include<chrono> //medir tempo
#include<iostream>
#include<fstream> //leitura de arquivos

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
	if(string(argv[1]) == "Kruskal")
	{
		start = chrono::system_clock::now();
		res = Kruskal(G,op,cost);
		end = chrono::system_clock::now();
	}
	else if(string(argv[1]) == "Prim")
	{
		start = chrono::system_clock::now();
		res = Prim(G,op,cost);
		end = chrono::system_clock::now();
	}
	chrono::milliseconds elapsed = chrono::duration_cast<chrono::milliseconds>(end-start);
	cout << "Tempo de execução do algoritmo: " << elapsed.count() << endl;
	outfile.open(argv[4],fstream::out);
	outfile << cost;
	for(unsigned int i = 0 ; i < res.size() ; i++)
		outfile << endl << res[i].va << ' ' << res[i].vb << ' ' << res[i].wgt;
	outfile.close();
	return 0;
}
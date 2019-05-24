#include "Graph_A.hpp" //Lista de adjacencias
#include "Graph_M.hpp" //Matriz de adjacencias
#include "Bellman_Ford.hpp"
#include "Dijkstra.hpp"
#include "Floyd_Warshall.hpp"
#include<vector>
#include<chrono> //medir tempo
#include<iostream>
#include<fstream> //leitura e escrita de arquivos

using namespace std;

void print_path(vector<int> pred, int vert, int source, fstream &out)
{
	if(vert == source)
		out << source;
	else if(pred[vert] != -1)
	{
		print_path(pred,pred[vert],source,out);
		out << fixed << ' ' << vert;
	}
}

Graph* initialize_graph(string alg, int nver) {
    if (alg == "floyd-warshall")
        return new Graph_M(nver);
    else
        return new Graph_A(nver);
}

int main(int argc, char * argv[])
{
	if(argc < 5)
	{
		cerr << "Uso: ./main <bellman-ford/dijkstra/floyd-warshall/johnson> <x> <arq-in> <arq-out>" << endl;
		return 1;
	}

	fstream infile,outfile;
	int nver,narestas,source,va,vb;
	float peso;
    vector<double> costs;
    vector<int> pred;
    vector<vector<float>> d_n;
    vector<vector<int>> p_n;

	infile.open(argv[3]);
	if(!infile.is_open())
	{
		cerr << "Problema na abertura do arquivo de entrada!" << endl;
		return 1;
	}

	cout << "Lendo grafo..." << endl;
	infile >> nver >> narestas >> source;
    Graph* G = initialize_graph(string(argv[1]), nver);
	for(int i = 0 ; i < narestas; i++)
	{
		infile >> va >> vb >> peso;
		G->add_edge(va,vb,peso);
	}
	infile.close();
    int op = argv[2][0] - '0';
    chrono::system_clock::time_point start,end;
    cout << "Iniciando algoritmo..." << endl;
    if(string(argv[1]) == "bellman-ford")
    {
        start = chrono::system_clock::now();
		if (Bellman_Ford((Graph_A &)*G,source,pred,costs)) {
			cout << "o grafo contém um ciclo de peso negativo" << endl;	
			return 1;
		}
        end = chrono::system_clock::now();
    }
    else if(string(argv[1]) == "dijkstra")
    {
        start = chrono::system_clock::now();
        pred = Dijkstra((Graph_A &)*G,op,source,costs);
        end = chrono::system_clock::now();
    }
    else if(string(argv[1]) == "floyd-warshall")
    {
        start = chrono::system_clock::now();
        p_n = Floyd_Warshall((Graph_M &)*G,op,d_n);
        end = chrono::system_clock::now();
    }
    else if(string(argv[1]) == "johnson")
    {
        start = chrono::system_clock::now();
        // johnson
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
	outfile.precision(4);
	for(int i = 0 ; i < G->n_vert ; i++)
	{
        if (string(argv[1]) == "floyd-warshall")
        {
            for(int j = 0 ; j < G->n_vert ; j++)
            {
                outfile << fixed << d_n[i][j] << ' ';
                print_path(p_n[i],j,i,outfile);
                outfile << endl;
            }
        } else {
            outfile << fixed << costs[i] << ' ';
            print_path(pred,i,source,outfile);
            outfile << endl;

        }
	}
	return 0;
}

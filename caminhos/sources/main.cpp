#include "Graph_A.hpp" //Lista de adjacencias
#include "Graph_M.hpp" //Matriz de adjacencias
#include "Bellman_Ford.hpp"
#include "Dijkstra.hpp"
#include "Floyd_Warshall.hpp"
#include "Johnson.hpp"
#include<vector>
#include<iostream>
#include<chrono> //medir tempo
#include<fstream> //leitura e escrita de arquivos

using namespace std;

bool print_path(vector<int> pred, int vert, int source, FILE *f)
{
	if(vert == source)
    {
		fprintf(f,"%d",source);
        return true;
    }
    else if(vert != -1)
    {
    	if(print_path(pred,pred[vert],source,f))
        {
            fprintf(f," %d",vert);
            return true;
        }
        return false;
    }
    else
        return false;
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

    FILE *in,*out;
	int nver,narestas,source,va,vb;
	double peso;
    vector<double> costs;
    vector<int> pred;
    vector<vector<double>> d_n;
    vector<vector<int>> p_n;

    in = fopen(argv[3],"r");
	if(!in)
	{
		cerr << "Problema na abertura do arquivo de entrada!" << endl;
		return 1;
	}

	cout << "Lendo grafo..." << endl;
    fscanf(in,"%d\n%d\n%d\n",&nver,&narestas,&source);
    Graph* G = initialize_graph(string(argv[1]), nver);
	for(int i = 0 ; i < narestas; i++)
	{
        fscanf(in,"%d %d %lf\n",&va,&vb,&peso);
		G->add_edge(va,vb,peso);
	}
    fclose(in);
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
        p_n = Johnson((Graph_A &)*G, d_n, op);        
        end = chrono::system_clock::now();
    }
    else
    {
        cerr << "Opção inválida" << endl;
        return 1;
    }
    chrono::milliseconds elapsed = chrono::duration_cast<chrono::milliseconds>(end-start);
    cout << "Tempo de execução do algoritmo: " << elapsed.count() << " ms" << endl;

    out = fopen(argv[4],"w");
    if(!out)
    {
        cerr << "Problema na abertura do arquivo de saída" << endl;
        return 1;
    }

	for(int i = 0 ; i < G->n_vert; i++)
	{
        if (string(argv[1]) == "floyd-warshall" || string(argv[1]) == "johnson")
        {
            for(int j = 0 ; j < G->n_vert ; j++)
            {
                fprintf(out,"%lf ",d_n[i][j]);
                print_path(p_n[i],j,i,out);
                fprintf(out,"\n");
            }
        }
        else
        {
            fprintf(out,"%lf ",costs[i]);
            print_path(pred,i,source,out);
            fprintf(out,"\n");

        }
	}
    delete G;
    fclose(out);
	return 0;
}

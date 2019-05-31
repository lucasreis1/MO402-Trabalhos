#include "Dinitz.hpp"
#include "Graph.hpp"
#include<vector>
#include<chrono> //medir tempo
#include<iostream>
#include<fstream> //leitura e escrita de arquivos

using namespace std;

int main(int argc, char * argv[])
{
	if(argc < 4)
	{
		cerr << "Uso: ./main <ford-fulkerson/edmonds-karp/dinitz> <arq-in> <arq-out>" << endl;
		return 1;
	}

    FILE *in,*out;
	int nver,narestas,s,t,va,vb,cap,f;
    in = fopen(argv[2],"r");
	if(!in)
	{
		cerr << "Problema na abertura do arquivo de entrada!" << endl;
		return 1;
	}

	cout << "Lendo grafo..." << endl;
    fscanf(in,"%d\n%d\n%d\n%d\n",&nver,&narestas,&s,&t);
    Graph G(nver);
	for(int i = 0 ; i < narestas; i++)
	{
        fscanf(in,"%d %d %d\n",&va,&vb,&cap);
		G.add_edge(va,vb,cap);
	}
    fclose(in);

    chrono::system_clock::time_point start,end;
    cout << "Iniciando algoritmo..." << endl;

    if(string(argv[1]) == "ford-fulkerson")
    {
        start = chrono::system_clock::now();
		//Ford-Fulkerson
        end = chrono::system_clock::now();
    }
    else if(string(argv[1]) == "edmonds-karp")
    {
        start = chrono::system_clock::now();
        //Edmonds-Karp
        end = chrono::system_clock::now();
    }
    else if(string(argv[1]) == "dinitz")
    {
        start = chrono::system_clock::now();
        f = Dinitz(G, s, t);
        end = chrono::system_clock::now();
    }
    else
    {
        cerr << "Opção inválida" << endl;
        return 1;
    }
    chrono::milliseconds elapsed = chrono::duration_cast<chrono::milliseconds>(end-start);
    cout << "Tempo de execução do algoritmo: " << elapsed.count() << " ms" << endl;

    out = fopen(argv[3],"w");
    if(!out)
    {
        cerr << "Problema na abertura do arquivo de saída" << endl;
        return 1;
    }

	for(int i = 0 ; i < G.n_vert; i++)
	{
        for (unsigned int j = 0; j < G.vertices[i].edg.size(); ++j)
        {
            if (!G.vertices[i].edg[j]->back)
            {
                int v = G.vertices[i].edg[j]->vb;
                fprintf(out, "%d %d %d\n", i, v, G.vertices[i].edg[j]->f);
            }
        }
	}

	std::cout << "fluxo máximo: " << f << std::endl;

    fclose(out);
	return 0;
}

#include<iostream>
#include<cmath>
#include<vector>
#include<string>
#include<random>
#include<time.h>


using namespace std;

struct Vertex
{
	int pos;
	float x;
	float y;
	Vertex(int p,float a,float b): pos(p),x(a),y(b){}
};

struct Edge
{
	int va;
	int vb;
	int wgt;
	Edge(int va=0, int vb=0, int w=0.0): va(va),vb(vb),wgt(w){}
};

int euclid_dist(float x1, float y1,float x2,float y2)
{
	return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}


int main(int argc, char* argv[])
{
	FILE *in,*out;
	vector<Vertex> vetor;
	vector<vector<Edge>> arestas;
	unsigned seed = time(NULL);
	minstd_rand0 rnd(seed);
	if(argc < 3)
	{
		cout << "Uso: ./tratamento_de_dados <f/s> <entrada.tsp> <source> <terminal> <\% criacao aresta>";
		return 1;
	}
	in = fopen(argv[2],"r");
	if(!in)
	{
		cerr << "Erro de leitura" << endl;
		return 1;
	}
	string p;
	char rdline[50];
	int i = 0;
	int n;
	string cmp_str = "";
	while(cmp_str.find("DIMENSION :") == string::npos)
	{
		fgets(rdline,sizeof(rdline),in);
		cmp_str = string(rdline);		
	}
	n = std::stoi(cmp_str.substr(12,cmp_str.size()-13));
	while(cmp_str.find("NODE_COORD_SECTION") == string::npos)
	{
		fgets(rdline,sizeof(rdline),in);
		cmp_str = string(rdline);
	}
	int id;
	float a,b;
	for(i = 0 ; i < n ; i++)
	{
		fscanf(in,"%d %f %f\n",&id,&a,&b);
		vetor.push_back(Vertex(id,a,b));
	}
	fclose(in);
	unsigned int sz = vetor.size();
	string pout = string(argv[2]);
	int filesize = string(argv[2]).size();
	i = pout.size() - 1;
	for(; i>=0 && pout[i] != '/'; i--)
		;
	i++;
	string out_file;
	if(string(argv[1]) == "f")
		out_file = pout.substr(i,filesize-i-4) + "-f.txt";
	else
		out_file = pout.substr(i,filesize-i-4) + "-" + string(argv[5]) + "\%.txt";
	out = fopen(out_file.c_str(),"w");
	if(!out)
	{
		cerr << "Erro de abertura" << endl;
		return 1;
	}
	cout << "Escrevendo arquivo" << endl;
	if(string(argv[1]) == "f")
	{
		fprintf(out,"%d\n%d\n%s\n%s",sz,sz*(sz-1)/2,argv[3],argv[4]);
		for(unsigned int i = 0 ; i < sz-1 ; i++)
		{
			for(unsigned int j = i+1 ; j < sz ; j++)
				fprintf(out,"\n%d %d %d",i,j,euclid_dist(vetor[i].x,vetor[i].y,vetor[j].x,vetor[j].y));
		}
	}
	else
	{
		arestas.resize(sz);
		vector<vector<char>> exists_edge(sz,vector<char> (sz,false));
		float chance = stof(argv[5])/100.0;
		unsigned int nar = 0;
		for(unsigned int i = 0 ; i < sz ; i++)
		{
			if(i%10000 == 0)
				std::cout << "Imprimindo vizinhos do vértice " << i << "...\n";
			for(unsigned int j = 0; j < sz ; j++)
			{
				if(i != j && !exists_edge[j][i]&& chance >= (double)rnd()/rnd.max())
				{
					arestas[i].push_back(Edge(i,j,euclid_dist(vetor[i].x,vetor[i].y,vetor[j].x,vetor[j].y)));
					nar++;
					exists_edge[i][j] == true;
				}
			}
		}
		fprintf(out,"%d\n%d\n%s\n%s",sz,nar,argv[3],argv[4]);
		for(unsigned int i = 0 ; i < sz ; i++)
		{
			for(unsigned int j = 0 ;j < arestas[i].size() ; j++)
				fprintf(out,"\n%d %d %d",arestas[i][j].va,arestas[i][j].vb,arestas[i][j].wgt);
		}
	}
	fclose(out);
	return 0;
}

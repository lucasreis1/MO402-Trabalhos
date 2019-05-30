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
	double wgt;
	Edge(int va=0, int vb=0, double w=0.0): va(va),vb(vb),wgt(w){}
};

float euclid_dist(float x1, float y1,float x2,float y2)
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
		cout << "Uso: ./tratamento_de_dados <f/s> <entrada.tsp> <source> <\% criacao aresta>";
		return 1;
	}
	in = fopen(argv[2],"r");
	if(!in)
	{
		cerr << "Erro de leitura" << endl;
		return 1;
	}
	string p;
	char c;
	int i = 0;
	while(i < 4)
	{
		c = fgetc(in);
		if(c == '\n')
			i++;
	}
	int n;
	fscanf(in,"DIMENSION : %d",&n);
	while(i < 7)
	{
		c = fgetc(in);
		if(c == '\n')
			i++;
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
	int filesize = string(argv[2]).size();
	string out_file = string(argv[2]).substr(0,filesize-4) + ".txt";
	out = fopen(out_file.c_str(),"w");
	if(!out)
	{
		cerr << "Erro de abertura" << endl;
		return 1;
	}
	cout << "Escrevendo arquivo" << endl;
	if(string(argv[1]) == "f")
	{
		fprintf(out,"%d\n%d\n%s",sz,sz*(sz-1)/2,argv[3]);
		for(unsigned int i = 0 ; i < sz ; i++)
		{
			for(unsigned int j = i+1 ; j < sz ; j++)
				fprintf(out,"\n%d %d %f",i,j,euclid_dist(vetor[i].x,vetor[i].y,vetor[j].x,vetor[j].y));
		}
	}
	else
	{
		arestas.resize(sz);
		float chance = stof(argv[4])/100.0;
		unsigned int nar = 0;
		for(unsigned int i = 0 ; i < sz ; i++)
		{
			if(i%10000 == 0)
				std::cout << "Imprimindo vizinhos do vértice " << i << "...\n";
			for(unsigned int j = 0 ;j < sz ; j++)
			{
				if(i != j && chance >= (double)rnd()/rnd.max())
				{
					arestas[i].push_back(Edge(i,j,euclid_dist(vetor[i].x,vetor[i].y,vetor[j].x,vetor[j].y)));
					nar++;
				}
			}
		}
		fprintf(out,"%d\n%d\n%s",sz,nar,argv[3]);
		for(unsigned int i = 0 ; i < sz ; i++)
		{
			for(unsigned int j = 0 ;j < arestas[i].size() ; j++)
				fprintf(out,"\n%d %d %f",arestas[i][j].va,arestas[i][j].vb,arestas[i][j].wgt);
		}
	}
	//out.close();
	fclose(out);
	return 0;
}
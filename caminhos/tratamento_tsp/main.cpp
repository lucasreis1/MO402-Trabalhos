#include<iostream>
#include<fstream>
#include<cmath>
#include<vector>
#include<string>

using namespace std;

struct Vertex
{
	int pos;
	float x;
	float y;
	Vertex(int p,float a,float b): pos(p),x(a),y(b){}
};

float euclid_dist(float x1, float y1,float x2,float y2)
{
	return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}


int main(int argc, char* argv[])
{
	fstream in;
	vector<Vertex> vetor;
	if(argc < 3)
	{
		cout << "Uso: ./tratamento_de_dados <f/s> <entrada.tsp> <saida.txt> <source> <num grau>";
		return 1;
	}
	in.open(argv[2]);
	if(!in.is_open())
	{
		cerr << "Erro de leitura" << endl;
		return 1;
	}
	string p;
	for(int i = 0 ; i < 7 ; i++)
		getline(in,p);
	int id;
	float a,b;
	while(in >> id >> a >> b)
		vetor.push_back(Vertex(id,a,b));
	in.close();
	unsigned int sz = vetor.size();
	int filesize = string(argv[2]).size();
	string out_file = string(argv[2]).substr(0,filesize-4) + ".txt";
	fstream out;
	out.open(out_file, ios::out);
	if(!out.is_open())
	{
		cerr << "Erro de abertura" << endl;
		return 1;
	}
	cout << "Escrevendo arquivo" << endl;
	if(string(argv[1]) == "f")
	{
		out << sz << endl <<sz*(sz-1)/2 << argv[3];
		for(unsigned int i = 0 ; i < sz ; i++)
		{
			for(unsigned int j = i+1 ; j < sz ; j++)
				out << fixed << endl << i << ' ' << j << ' ' << euclid_dist(vetor[i].x,vetor[i].y,vetor[j].x,vetor[j].y);
		}
	}
	else
	{
		unsigned int n_ar = stoi(argv[4]);
		out << sz << endl << sz*n_ar << endl << argv[3];
		for(unsigned int i = 0 ; i < sz ; i++)
		{
			unsigned int j = (i+1)%sz;
			for(unsigned int k = 0 ; k < n_ar ; k++)
			{
				out << fixed << endl << i << ' ' << j << ' ' << euclid_dist(vetor[i].x,vetor[i].y,vetor[j].x,vetor[j].y);
				j = (j+1)%sz;
			}

		}
	}
	out.close();
	return 0;
}
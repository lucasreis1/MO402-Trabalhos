#include<iostream>
#include<fstream>
#include<cmath>
#include<vector>

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
	in.open(argv[1]);
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
	int filesize = string(argv[1]).size();
	string out_file = string(argv[1]).substr(0,filesize-4) + ".txt";
	fstream out;
	cout << out_file << endl;
	out.open(out_file, ios::out);
	if(!out.is_open())
	{
		cerr << "Erro de abertura" << endl;
		return 1;
	}
	cout << "Escrevendo arquivo" << endl;
	out.precision(3);
	out << sz << endl <<sz*(sz-1)/2;
	for(unsigned int i = 0 ; i < sz ; i++)
	{
		for(unsigned int j = i+1 ; j < sz ; j++)
			out << fixed << endl << i << ' ' << j << ' ' << euclid_dist(vetor[i].x,vetor[i].y,vetor[j].x,vetor[j].y);
	}
	out.close();
	return 0;
}
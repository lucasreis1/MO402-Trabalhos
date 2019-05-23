#include "Dijkstra.hpp"
#include<limits> //max_float
#include<iostream>

using std::vector;

Queue * create_priority_queue(int op, int size, int src)
{
    Queue * Q = NULL;
    switch(op)
    {
        case 0:
        {
            Q = new Heap(size, src);
            break;
        }
        case 1:
        {
            Q = new NaivePriorityQueue(size, src);
            break;
        }
        case 2:
            Q = new Fibonacci(size, src);
            break;
        default:
            std::cerr << "Opção inválida" << std::endl;
            exit(1);
    }

    return Q;
}

vector<int> Dijkstra(Graph_A &G, int op, int source, vector<double> &d)
{
    vector<int> pred(G.n_vert,-1);
    d.resize(G.n_vert);
    for(int i = 0 ; i < G.n_vert ; i++)
    {
        if(i != source)
            d[i] = std::numeric_limits<float>::max();
    }
    d[source] = 0.0;
    pred[source] = source;
    Queue * Q = create_priority_queue(op, G.n_vert, source);

    while (Q->tam > 0)
    {
        int u = Q->extract_min();
        int nadj = G.vertices[u].n_edges;
        for(int i = 0 ; i < nadj ; i++)
        {
            int va = G.vertices[u].edg[i]->va;
            int vb = G.vertices[u].edg[i]->vb;
            float w = G.vertices[u].edg[i]->wgt;
            if(Q->in_queue(vb) && d[vb] > d[va] + w)
            {
                pred[vb] = va;
                d[vb] = d[va] + w;
                Q->decrease_key(vb,d[va] + w);
            }
        }
    }
    delete Q;
    return pred;
}
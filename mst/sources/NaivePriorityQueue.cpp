#include "NaivePriorityQueue.hpp"
#include <iostream>
#include <algorithm>

NaivePriorityQueue::NaivePriorityQueue(int nel, int src): Queue(nel), Q(tam)
{
    build_heap(src);
}

void NaivePriorityQueue::build_heap(int src) {
    Q[src].vert = src;
    Q[src].val = 0.0;
    for(int i = 0 ; i < tam ; i++)
    {
        if(i != src)
        {
            Q[i].vert = i;
            Q[i].val = std::numeric_limits<float>::max();
        }
    }
}

int NaivePriorityQueue::extract_min() {
    if(tam < 1)
    {
        std::cerr << "Erro no tamanho do heap" << std::endl;
        exit(1);
    }
    float min = 0.0;
    int min_vert = 0;
    int min_index = 0;
    for (int i = 0 ; i < tam ; i++)
    {
        if (Q[i].val < min || i == 0) {
            min = Q[i].val;
            min_vert = Q[i].vert;
            min_index = i;
        }
    }

    Q.erase(Q.begin() + min_index);
    tam--;
    return min_vert;
}

void NaivePriorityQueue::decrease_key(int vert, float key) {
    for (int i = 0 ; i < tam ; i++)
    {
        if (Q[i].vert == vert)
            Q[i].val = key;
    }
}

bool NaivePriorityQueue::in_queue(int vert) {
    for (int i = 0 ; i < tam ; i++)
    {
        if (Q[i].vert == vert)
            return true;
    }
    return false;
}

float NaivePriorityQueue::get_value(int vert) {
    for (int i = 0 ; i < tam ; i++)
    {
        if (Q[i].vert == vert)
            return Q[i].val;
    }
    return 0.0;
}


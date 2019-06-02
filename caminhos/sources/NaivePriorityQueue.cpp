#include "NaivePriorityQueue.hpp"
#include <iostream>
#include <algorithm>

NaivePriorityQueue::NaivePriorityQueue(int nel, int src): Queue(nel), Q(tam)
{
    for(int i = 0 ; i < tam ; i++)
    {
        if(i != src)
            Q[i].val = std::numeric_limits<double>::max();
    }
}

int NaivePriorityQueue::extract_min() {
    if(tam < 1)
    {
        std::cerr << "Erro no tamanho do heap" << std::endl;
        exit(1);
    }
    double min = std::numeric_limits<double>::infinity();
    int min_index = 0;
    for (unsigned int i = 0 ; i < Q.size() ; i++)
    {
        if ((Q[i].val <= min || i== 0) && Q[i].is_inqueue) {
            min = Q[i].val;
            min_index = i;
        }
    }
    Q[min_index].is_inqueue = false;
    tam--;
    return min_index;
}

void NaivePriorityQueue::decrease_key(int vert, double key) {
    if(Q[vert].val < key || Q[vert].is_inqueue == false)
    {
        std::cerr << "Erro na redução de key" << std::endl; 
        exit(1);
    }
    Q[vert].val = key;
}

double NaivePriorityQueue::get_value(int vert) {
    if(Q[vert].is_inqueue == false)
    {
        std::cerr << "Erro na aquisiçao de valor na fila" << std::endl;
        exit(1);
    }
    return Q[vert].val;
}
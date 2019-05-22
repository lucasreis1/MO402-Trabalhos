#include "Graph_A.hpp"
#include "Heap.hpp"
#include "NaivePriorityQueue.hpp"
#include "Fibonacci.hpp"

Queue * create_priority_queue(int op, int size, int src);
vector<int> Dijkstra(Graph_A &G, int op, int src, vector<double> &d);
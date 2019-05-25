#include "Queue.hpp"
#include<vector>

using std::vector;

class NaivePriorityQueue: public Queue
{
private:

    struct Node
    {
        double val;
        bool is_inqueue;

        Node(double vl=0.0): val(vl),is_inqueue(true){}
    };

    vector<Node> Q;

public:
    NaivePriorityQueue(int nel,int src);

    void build_heap(int src);

    int extract_min();

    void decrease_key(int vert, double key);

    bool in_queue(int vert);

    double get_value(int vert);
};
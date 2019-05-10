#include "Queue.hpp"
#include<vector>

using std::vector;

class NaivePriorityQueue: public Queue
{
private:

    struct Node
    {
        float val;
        bool is_inqueue;

        Node(float vl=0.0): val(vl),is_inqueue(true){}
    };

    vector<Node> Q;

public:
    NaivePriorityQueue(int nel,int src);

    void build_heap(int src);

    int extract_min();

    void decrease_key(int vert, float key);

    bool in_queue(int vert);

    float get_value(int vert);
};
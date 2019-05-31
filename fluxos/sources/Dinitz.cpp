#include "Dinitz.hpp"
#include <iostream>
#include <queue>
#include <limits>

bool layers(Graph &G, vector<int> &layer, const int &s, const int &t)
{
    int n_vert = G.n_vert;
    vector<int> visited(n_vert);
    std::queue<int> q;
    for (int i = 0 ; i < n_vert ; ++i)
    {
        visited[i] = 0;
        layer[i] = 0;
    }
    visited[s] = 1;
    layer[s] = 0;
    q.push(s);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (unsigned int i = 0;i < G.vertices[u].edg.size();++i)
        {
            if (!G.vertices[u].edg[i]->fres)
                continue;
            int vb = G.vertices[u].edg[i]->vb;
            if (!visited[vb])
            {
                visited[vb] = 1;
                q.push(vb);
                layer[vb] = layer[u] + 1;
            }
        }
    }
    return visited[t] == 1;
}

bool find_path(Graph &G, vector<int> &layer, vector<Edge *> &S, const int &u, const int &t)
{
    if (u == t)
        return true;
    for (unsigned int i = 0;i < G.vertices[u].edg.size();++i)
    {
        int v = G.vertices[u].edg[i]->vb;
        if (G.vertices[u].edg[i]->fres == 0 || G.vertices[u].edg[i]->blocked || layer[u] + 1 != layer[v])
            continue;
        if (!find_path(G, layer, S, v, t))
        {
            G.vertices[u].edg[i]->blocked = true;
        }
        else
        {
            S.push_back(G.vertices[u].edg[i]);
            return true;
        }
    }
    return false;
}

void increase_flow(Graph &G, vector<Edge *> &S)
{
    int cp = std::numeric_limits<int>::max();
    Edge *e;

    for (vector<Edge *>::iterator it = S.begin(); it != S.end(); ++it)
    {
        e = *it;
        cp = std::min(cp, e->fres);
    }
    for (vector<Edge *>::iterator it = S.begin(); it != S.end(); ++it)
    {
        e = *it;
        if (!e->back)
        {
            e->f += cp;
            e->fres = e->cap - e->f;
            G.edges[e->rev]->fres = e->f;

            if (e->f == e->cap)
            {
                e->blocked = true;
                G.edges[e->rev]->blocked = true;
            }
        }
        else
        {
            G.edges[e->rev]->f -= cp;
            G.edges[e->rev]->fres = G.edges[e->rev]->cap - G.edges[e->rev]->f;
            e->fres = G.edges[e->rev]->f;

            if (G.edges[e->rev]->f == G.edges[e->rev]->cap)
            {
                e->blocked = true;
                G.edges[e->rev]->blocked = true;
            }
        }
    }
    S.clear();
}

bool maximal(Graph &G, vector<int> &layer, const int &s, const int &t)
{
    int n_edges = G.n_edges;
    bool f_l = false;
    vector<Edge *> S;

    for (int i = 0; i < n_edges; ++i)
    {
        G.edges[i]->blocked = false;
    }

    while(find_path(G, layer, S, s, t))
    {
        increase_flow(G, S);
        f_l = true;
    }
    return f_l;
}

int get_flow_value(Graph &G, const int &s)
{
    int flow = 0;
    for (unsigned int i = 0; i < G.vertices[s].edg.size(); ++i)
    {
        flow += G.vertices[s].edg[i]->f;
    }
    return flow;
}

int Dinitz(Graph &G, int s, int t)
{
    const int n_vert = G.n_vert;
    vector<int> layer(n_vert);

    layers(G, layer, s, t);
    bool f_l = maximal(G, layer, s, t);

    while (f_l)
    {
        if (layers(G, layer, s, t))
        {
            f_l = maximal(G, layer, s, t);
        }
        else
        {
            break;
        }
    }

    return get_flow_value(G, s);
}
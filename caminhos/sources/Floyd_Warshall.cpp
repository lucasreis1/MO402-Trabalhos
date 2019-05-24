#include "Floyd_Warshall.hpp"
#include <iostream>
#include <limits> //max_float

void initialize_sp_matrix(vector<vector<float>> &D, int n_vert)
{
    D.resize(n_vert);
    for (int i = 0; i < n_vert; ++i)
    {
        D[i].resize(n_vert);
    }
}

void initialize_pr_matrix(vector<vector<int>> &P, int n_vert)
{
    P.resize(n_vert);
    for (int i = 0; i < n_vert; ++i)
    {
        P[i].resize(n_vert);
    }
}

void initialize_sp_weights(vector<vector<float>> &D, Graph_M &G)
{
    int n_vert = G.n_vert;
    for(int i = 0 ; i < n_vert ; i++)
    {
        for(int j = 0 ; j < n_vert ; j++)
        {
            D[i][j] = G.edges[i][j].w;
        }
    }
}

void print_sp_matrix(vector<vector<float>> &D, int n_vert)
{
    for(int i = 0 ; i < n_vert ; i++)
    {
        for(int j = 0 ; j < n_vert ; j++)
        {
            if (D[i][j] == std::numeric_limits<float>::max())
                std::cout << "INF";
            else
                std::cout << D[i][j];
            std::cout << '\t';
        }
        std::cout << std::endl;
    }
}

void print_pr_matrix(vector<vector<int>> &D, int n_vert)
{
    for(int i = 0 ; i < n_vert ; i++)
    {
        for(int j = 0 ; j < n_vert ; j++)
        {
            if (D[i][j] == std::numeric_limits<int>::max())
                std::cout << "NIL";
            else
                std::cout << D[i][j];
            std::cout << '\t';
        }
        std::cout << std::endl;
    }
}

vector<vector<int>> Floyd_Warshall(Graph_M &G, int op, vector<vector<float>> &d)
{
    int n_vert = G.n_vert;

    vector<vector<float>> d_p;
    vector<vector<int>> p_p;
    vector<vector<int>> p_n;
    initialize_sp_matrix(d, n_vert);
    initialize_pr_matrix(p_n, n_vert);
    initialize_sp_weights(d, G);

    for (int i = 0 ; i < n_vert ; ++i)
    {
        for (int j = 0 ; j < n_vert ; ++j)
        {
            if (i != j && d[i][j] < std::numeric_limits<float>::max())
                p_n[i][j] = i;
            else
                p_n[i][j] = std::numeric_limits<int>::max();
        }
    }

    switch(op)
    {
        case 0:
        {
            // Floyd-Warshall
            for (int k = 0 ; k < n_vert ; ++k)
            {
                d_p = d;
                p_p = p_n;
                for (int i = 0 ; i < n_vert ; ++i)
                {
                    for (int j = 0 ; j < n_vert ; ++j)
                    {
                        if (d_p[i][k] + d_p[k][j] < d_p[i][j])
                        {
                            d[i][j] = d_p[i][k] + d_p[k][j];
                            p_n[i][j] = p_p[k][j];
                        }
                    }
                }
            }
            return p_n;
            // Fim do Floyd_Warshall
        }
        case 1:
        {
            // Slow All-Pairs Shortest Paths
            for (int m = 1 ; m < n_vert ; ++m)
            {
                d_p = d;
                p_p = p_n;
                for (int i = 0 ; i < n_vert ; ++i)
                {
                    for (int j = 0 ; j < n_vert ; ++j)
                    {
                        for (int k = 0 ; k < n_vert ; ++k)
                        {
                            if (d_p[i][k] + G.edges[k][j].w < d[i][j]) {
                                d[i][j] = d_p[i][k] + G.edges[k][j].w;
                                p_n[i][j] = p_p[k][j];
                            }
                        }
                    }
                }
            }
            return p_n;
            // Fim do Slow All-Pairs Shortest Paths
        }
        case 2:
        {
            // Faster All-Pairs Shortest Paths
            int m = 1;

            while (m < n_vert - 1) {
                d_p = d;
                p_p = p_n;
                for (int i = 0 ; i < n_vert ; ++i)
                {
                    for (int j = 0 ; j < n_vert ; ++j)
                    {
                        for (int k = 0 ; k < n_vert ; ++k)
                        {
                            if (d_p[i][k] + d_p[k][j] < d[i][j]) {
                                d[i][j] = d_p[i][k] + d_p[k][j];
                                p_n[i][j] = p_p[k][j];
                            }
                        }
                    }
                }
                m *= 2;
            }
            return p_n;
            // Fim do Faster All-Pairs Shortest Paths
        }
        default:
            std::cerr << "Opção inválida" << std::endl;
            exit(1);
    }

    return {};
}
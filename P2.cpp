#include <iostream>
#include <vector>
#include <limits.h>
#include <queue>
#include <string.h>

#define PROCESSERS 2

using namespace std;

class Graph
{
    int N; // Number of vertices (number of processes + number of processers)
    vector<vector<int>> adj_matrix;

public:
    Graph(int N);
    void AddProcessingCost(int u, int weight_x, int weight_y);
    void AddCommCost(int u, int v, int weight);
    void PrintGraph();
    bool BFS(vector<vector<int>> &rGraph, int parent[]);
    int FordFulkerson();
};

Graph::Graph(int processes)
{
    this->N = processes + PROCESSERS;

    adj_matrix.resize(N, vector<int>(N, 0));
}

void Graph::AddProcessingCost(int u, int weight_x, int weight_y)
{
    adj_matrix[N - 2][u] = weight_x;
    adj_matrix[u][N - 1] = weight_y;
}

void Graph::AddCommCost(int u, int v, int weight)
{
    adj_matrix[u - 1][v - 1] = weight;
    adj_matrix[v - 1][u - 1] = weight;
}

void Graph::PrintGraph()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            cout << adj_matrix[i][j] << " ";
        cout << endl;
    }
}

bool Graph::BFS(vector<vector<int>> &rGraph, int parent[])
{
    bool visited[N];
    memset(visited, 0, sizeof(visited));

    queue<int> q;
    q.push(N - 2);
    visited[N - 2] = true;
    parent[N - 2] = -1;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int v = 0; v < N; v++)
        {
            if (visited[v] == false && rGraph[u][v] > 0)
            {

                if (v == N - 1)
                {
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    return false;
}

int Graph::FordFulkerson()
{
    int u, v;

    vector<vector<int>> rGraph;

    rGraph.resize(N, vector<int>(N));

    for (u = 0; u < N; u++)
        for (v = 0; v < N; v++)
            rGraph[u][v] = adj_matrix[u][v];

    int parent[N];

    int max_flow = 0;

    while (BFS(rGraph, parent))
    {
        int path_flow = INT_MAX;
        for (v = N - 1; v != N - 2; v = parent[v])
        {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }

        for (v = N - 1; v != N - 2; v = parent[v])
        {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        max_flow += path_flow;
    }

    return max_flow;
}

Graph parseInput()
{
    int n, k;

    scanf("%d %d", &n, &k);

    Graph g = Graph(n);

    int cost_x, cost_y;

    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &cost_x, &cost_y);
        g.AddProcessingCost(i, cost_x, cost_y);
    }

    int i, j, cost;

    for (int m = 0; m < k; m++)
    {
        scanf("%d %d %d", &i, &j, &cost);
        g.AddCommCost(i, j, cost);
    }

    return g;
}

int main()
{
    Graph g = parseInput();

    int total_cost = g.FordFulkerson();

    cout << total_cost << endl;

    return 0;
}
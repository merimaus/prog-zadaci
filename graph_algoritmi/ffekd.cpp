#include <iostream>
#include <climits>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

class GraphList 
{
public:
    int V;
    vector<vector<int>> adj;
    vector<vector<int>> cap;

    GraphList(int V) 
    {
        this->V = V;
        adj.resize(V);
        cap.resize(V, vector<int>(V, 0));
    }

    void addEdge(int u, int v, int capacity) 
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
        cap[u][v] = capacity;
    }

    bool bfs(int s, int t, int parent[]) 
    {
        bool vis[V];
        for (int i = 0; i < V; i++) 
        {
            vis[i] = false;
        }
        queue<int> q;
        q.push(s);
        vis[s] = true;
        parent[s] = -1;

        while (!q.empty()) 
        {
            int u = q.front();
            q.pop();

            for (int i = 0; i < adj[u].size(); i++) 
            {
                int v = adj[u][i];
                if (!vis[v] && cap[u][v] > 0) 
                {
                    q.push(v);
                    parent[v] = u;
                    vis[v] = true;
                }
            }
        }
        return vis[t];
    }

    int dfs(int u, int t, int flow, int parent[]) 
    {
        if (u == t)
        {
            return flow;
        }
        for (int i = 0; i < adj[u].size(); i++)
        {
            int v = adj[u][i]; 
            if (parent[v] == -1 && cap[u][v] > 0) 
            {
                parent[v] = u;
                int curr_flow = min(flow, cap[u][v]);
                int temp_flow = dfs(v, t, curr_flow, parent);
                
                if (temp_flow > 0) 
                {
                    cap[u][v] -= temp_flow;
                    cap[v][u] += temp_flow;
                    return temp_flow;
                }
            }
        }
        return 0;
    }

    int solveFordFulkerson(int s, int t) 
    {
        int u, v;
        int parent[V];
        int max_flow = 0;

        while (bfs(s, t, parent)) 
        {
            int path_flow = INT_MAX;
            for (v = t; v != s; v = parent[v]) 
            {
                u = parent[v];
                path_flow = min(path_flow, cap[u][v]);
            }
            for (v = t; v != s; v = parent[v]) 
            {
                u = parent[v];
                cap[u][v] -= path_flow;
                cap[v][u] += path_flow;
            }
            max_flow += path_flow;
        }
        return max_flow;
    }

    int solveEdmondsKarp(int s, int t) 
    {
        int u, v;
        int parent[V];
        int max_flow = 0;

        while (bfs(s, t, parent)) 
        {
            int path_flow = INT_MAX;
            for (v = t; v != s; v = parent[v]) 
            {
                u = parent[v];
                path_flow = min(path_flow, cap[u][v]);
            }
            for (v = t; v != s; v = parent[v]) 
            {
                u = parent[v];
                cap[u][v] -= path_flow;
                cap[v][u] += path_flow;
            }
            max_flow += path_flow;
        }
        return max_flow;
    }

    int solveDinic(int s, int t) 
    {
        int max_flow = 0;
        int level[V];
        int parent[V];

        while (bfs(s, t, level)) 
        {
            for (int i = 0; i < V; i++) 
            {
                parent[i] = -1;
            }
            while (true) 
            {
                int flow = dfs(s, t, INT_MAX, parent);
                if (flow == 0) break;
                max_flow += flow;
            }
        }
        return max_flow;
    }

    void minCut(int s, int t) 
    {
        bool vis[V];
        queue<int> q;
        for (int i = 0; i < V; i++) 
        {
            vis[i] = false;
        }
        q.push(s);
        vis[s] = true;

        while (!q.empty()) 
        {
            int u = q.front();
            q.pop();
            for (int i = 0; i < adj[u].size(); i++) 
            {
                int v = adj[u][i];
                if (!vis[v] && cap[u][v] > 0) 
                {
                    vis[v] = true;
                    q.push(v);
                }
            }
        }

        for (int u = 0; u < V; u++) 
        {
            for (int i = 0; i < adj[u].size(); i++) 
            {
                int v = adj[u][i];
                if (vis[u] && !vis[v] && cap[u][v] == 0) 
                {
                    cout << u << " - " << v << endl;
                }
            }
        }
    }
};

class GraphMatrix 
{
public:
    int **cap;
    int V;

    GraphMatrix(int V) 
    {
        this->V = V;
        cap = new int*[V];
        for (int i = 0; i < V; i++) 
        {
            cap[i] = new int[V];
            for (int j = 0; j < V; j++) 
            {
                cap[i][j] = 0;
            }
        }
    }

    void addEdge(int u, int v, int capacity) 
    {
        cap[u][v] = capacity;
    }

    bool bfs(int s, int t, int parent[]) 
    {
        bool vis[V];
        for (int i = 0; i < V; i++) 
        {
            vis[i] = false;
        }
        queue<int> q;
        q.push(s);
        vis[s] = true;
        parent[s] = -1;

        while (!q.empty()) 
        {
            int u = q.front();
            q.pop();

            for (int v = 0; v < V; v++) 
            {
                if (!vis[v] && cap[u][v] > 0) 
                {
                    q.push(v);
                    parent[v] = u;
                    vis[v] = true;
                }
            }
        }
        return vis[t];
    }

    int dfs(int u, int t, int flow, int parent[]) 
    {
        if (u == t)
        {
            return flow;
        }
        for (int v = 0; v < V; v++) 
        {
            if (parent[v] == -1 && cap[u][v] > 0) 
            {
                parent[v] = u;
                int curr_flow = min(flow, cap[u][v]);
                int temp_flow = dfs(v, t, curr_flow, parent);
                if (temp_flow > 0) 
                {
                    cap[u][v] -= temp_flow;
                    cap[v][u] += temp_flow;
                    return temp_flow;
                }
            }
        }
        return 0;
    }

    int solveDinic(int s, int t) 
    {
        int max_flow = 0;
        int level[V];
        int parent[V];

        while(bfs(s, t, level)) 
        {
            for (int i = 0; i < V; i++) 
            {
                parent[i] = -1;
            }
            while(true) 
            {
                int flow = dfs(s, t, INT_MAX, parent);
                if (flow == 0) break;
                max_flow += flow;
            }
        }
        return max_flow;
    }

    int solveFordFulkerson(int s, int t) 
    {
        int u, v;
        int parent[V];
        int max_flow = 0;

        while (bfs(s, t, parent)) 
        {
            int path_flow = INT_MAX;
            for (v = t; v != s; v = parent[v]) 
            {
                u = parent[v];
                path_flow = min(path_flow, cap[u][v]);
            }
            for (v = t; v != s; v = parent[v]) 
            {
                u = parent[v];
                cap[u][v] -= path_flow;
                cap[v][u] += path_flow;
            }
            max_flow += path_flow;
        }
        return max_flow;
    }

    int solveEdmondsKarp(int s, int t) 
    {
        int u, v;
        int parent[V];
        int max_flow = 0;

        while (bfs(s, t, parent)) 
        {
            int path_flow = INT_MAX;
            for (v = t; v != s; v = parent[v]) 
            {
                u = parent[v];
                path_flow = min(path_flow, cap[u][v]);
            }
            for (v = t; v != s; v = parent[v]) 
            {
                u = parent[v];
                cap[u][v] -= path_flow;
                cap[v][u] += path_flow;
            }
            max_flow += path_flow;
        }
        return max_flow;
    }

    void minCut(int s, int t) 
    {
        bool* vis = new bool[V];
        queue<int> q;
        for (int i = 0; i < V; i++) 
        {
            vis[i] = false;
        }
        q.push(s);
        vis[s] = true;

        while (!q.empty()) 
        {
            int u = q.front();
            q.pop();
            for (int v = 0; v < V; v++) 
            {
                if (!vis[v] && cap[u][v] > 0) 
                {
                    vis[v] = true;
                    q.push(v);
                }
            }
        }
        for (int u = 0; u < V; u++) 
        {
            for (int v = 0; v < V; v++) 
            {
                if (vis[u] && !vis[v] && cap[u][v] == 0) 
                {
                    cout << u << " - " << v << endl;
                }
            }
        }
        delete[] vis;
    }

    ~GraphMatrix() 
    {
        for (int i = 0; i < V; i++) 
        {
            delete[] cap[i];
        }
        delete[] cap;
    }
};

int main() 
{
    GraphMatrix g1(6);
    g1.addEdge(0, 1, 16);
    g1.addEdge(0, 2, 13);
    g1.addEdge(1, 2, 10);
    g1.addEdge(1, 3, 12);
    g1.addEdge(2, 1, 4);
    g1.addEdge(2, 4, 14);
    g1.addEdge(3, 2, 9);
    g1.addEdge(3, 5, 20);
    g1.addEdge(4, 3, 7);
    g1.addEdge(4, 5, 4);

    cout << "Matrix and Edmonds-Karp: " << g1.solveEdmondsKarp(0, 5) << endl;
    g1.minCut(0, 5);

    GraphList g2(6);
    g2.addEdge(0, 1, 16);
    g2.addEdge(0, 2, 13);
    g2.addEdge(1, 2, 10);
    g2.addEdge(1, 3, 12);
    g2.addEdge(2, 1, 4);
    g2.addEdge(2, 4, 14);
    g2.addEdge(3, 2, 9);
    g2.addEdge(3, 5, 20);
    g2.addEdge(4, 3, 7);
    g2.addEdge(4, 5, 4);

    cout << "List and Edmonds-Karp: " << g2.solveEdmondsKarp(0, 5) << endl;
    g2.minCut(0, 5);

    return 0;
}
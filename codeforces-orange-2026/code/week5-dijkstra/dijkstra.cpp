#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, int> pli;

const ll INF = 1e18;

// Dijkstra: кратчайший путь от исходной вершины
vector<ll> dijkstra(int n, vector<vector<pair<int, ll>>>& graph, int start) {
    vector<ll> dist(n, INF);
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    
    dist[start] = 0;
    pq.push({0, start});
    
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        
        if (d > dist[u]) continue;
        
        for (auto [v, w] : graph[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    
    return dist;
}

// Dijkstra с восстановлением пути
pair<vector<ll>, vector<int>> dijkstraWithPath(int n, vector<vector<pair<int, ll>>>& graph, int start) {
    vector<ll> dist(n, INF);
    vector<int> parent(n, -1);
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    
    dist[start] = 0;
    pq.push({0, start});
    
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        
        if (d > dist[u]) continue;
        
        for (auto [v, w] : graph[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
    
    return {dist, parent};
}

// Восстановление пути
vector<int> getPath(int target, vector<int>& parent) {
    vector<int> path;
    int v = target;
    while (v != -1) {
        path.push_back(v);
        v = parent[v];
    }
    reverse(path.begin(), path.end());
    return path;
}

// Bellman-Ford: для графов с отрицательными рёбрами
vector<ll> bellmanFord(int n, vector<tuple<int, int, ll>>& edges, int start) {
    vector<ll> dist(n, INF);
    dist[start] = 0;
    
    for (int i = 0; i < n - 1; i++) {
        for (auto [u, v, w] : edges) {
            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }
    
    return dist;
}

// Проверка на отрицательный цикл
bool hasNegativeCycle(int n, vector<tuple<int, int, ll>>& edges) {
    vector<ll> dist(n, INF);
    dist[0] = 0;
    
    for (int i = 0; i < n - 1; i++) {
        for (auto [u, v, w] : edges) {
            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }
    
    for (auto [u, v, w] : edges) {
        if (dist[u] != INF && dist[u] + w < dist[v]) {
            return true;
        }
    }
    
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // Пример графа
    int n = 5;
    vector<vector<pair<int, ll>>> graph(n);
    
    // Добавляем рёбра (u, v, weight)
    graph[0].push_back({1, 4});
    graph[0].push_back({2, 1});
    graph[2].push_back({1, 2});
    graph[1].push_back({3, 1});
    graph[2].push_back({3, 5});
    graph[3].push_back({4, 3});
    
    // Dijkstra от вершины 0
    vector<ll> dist = dijkstra(n, graph, 0);
    cout << "Distances from vertex 0:\n";
    for (int i = 0; i < n; i++) {
        if (dist[i] == INF) cout << "INF ";
        else cout << dist[i] << " ";
    }
    cout << "\n";
    
    // Dijkstra с путём
    auto [dist2, parent] = dijkstraWithPath(n, graph, 0);
    cout << "Path from 0 to 4: ";
    vector<int> path = getPath(4, parent);
    for (int v : path) cout << v << " ";
    cout << "\n";
    
    return 0;
}

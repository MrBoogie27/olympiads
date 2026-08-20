#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, int> pli;

const ll INF = 1e18;

// Алгоритм Прима для MST (с приоритетной очередью)
ll prim(int n, vector<vector<pair<int, ll>>>& graph, int start = 0) {
    vector<bool> inMST(n, false);
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    
    ll mstWeight = 0;
    pq.push({0, start});
    
    while (!pq.empty()) {
        auto [w, u] = pq.top();
        pq.pop();
        
        if (inMST[u]) continue;
        
        inMST[u] = true;
        mstWeight += w;
        
        for (auto [v, weight] : graph[u]) {
            if (!inMST[v]) {
                pq.push({weight, v});
            }
        }
    }
    
    return mstWeight;
}

// Прим с возвратом рёбер MST
pair<ll, vector<pair<int, int>>> primWithEdges(int n, vector<vector<pair<int, ll>>>& graph, int start = 0) {
    vector<bool> inMST(n, false);
    vector<ll> key(n, INF);
    vector<int> parent(n, -1);
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    
    ll mstWeight = 0;
    vector<pair<int, int>> mstEdges;
    
    key[start] = 0;
    pq.push({0, start});
    
    while (!pq.empty()) {
        auto [w, u] = pq.top();
        pq.pop();
        
        if (inMST[u]) continue;
        
        inMST[u] = true;
        if (parent[u] != -1) {
            mstEdges.push_back({parent[u], u});
            mstWeight += w;
        }
        
        for (auto [v, weight] : graph[u]) {
            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
                pq.push({weight, v});
            }
        }
    }
    
    return {mstWeight, mstEdges};
}

// Прим без приоритетной очереди (для плотных графов)
ll primSimple(int n, vector<vector<pair<int, ll>>>& graph) {
    vector<bool> inMST(n, false);
    vector<ll> key(n, INF);
    
    key[0] = 0;
    ll mstWeight = 0;
    
    for (int count = 0; count < n; count++) {
        int u = -1;
        
        // Найти вершину с минимальным key, не в MST
        for (int v = 0; v < n; v++) {
            if (!inMST[v] && (u == -1 || key[v] < key[u])) {
                u = v;
            }
        }
        
        inMST[u] = true;
        mstWeight += key[u];
        
        // Обновить key соседей u
        for (auto [v, w] : graph[u]) {
            if (!inMST[v] && w < key[v]) {
                key[v] = w;
            }
        }
    }
    
    return mstWeight;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // Пример: 5 вершин
    int n = 5;
    vector<vector<pair<int, ll>>> graph(n);
    
    // Добавляем рёбра (v, weight)
    graph[0].push_back({1, 2});
    graph[0].push_back({3, 6});
    graph[1].push_back({0, 2});
    graph[1].push_back({2, 3});
    graph[1].push_back({3, 8});
    graph[1].push_back({4, 5});
    graph[2].push_back({1, 3});
    graph[2].push_back({4, 7});
    graph[3].push_back({0, 6});
    graph[3].push_back({1, 8});
    graph[4].push_back({1, 5});
    graph[4].push_back({2, 7});
    
    // Прим с приоритетной очередью
    ll mstWeight1 = prim(n, graph, 0);
    cout << "MST weight (Prim with PQ): " << mstWeight1 << "\n";
    
    // Прим с рёбрами
    auto [mstWeight2, mstEdges] = primWithEdges(n, graph, 0);
    cout << "MST weight (Prim with edges): " << mstWeight2 << "\n";
    cout << "MST edges:\n";
    for (auto [u, v] : mstEdges) {
        cout << u << " - " << v << "\n";
    }
    
    // Прим простой версией
    ll mstWeight3 = primSimple(n, graph);
    cout << "MST weight (Prim simple): " << mstWeight3 << "\n";
    
    return 0;
}

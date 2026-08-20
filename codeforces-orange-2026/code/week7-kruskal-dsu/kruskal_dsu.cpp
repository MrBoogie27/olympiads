#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef tuple<ll, int, int> edge; // вес, u, v

// Система непересекающихся множеств (DSU / Union-Find)
class DSU {
public:
    vector<int> parent, rank;
    
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    // Найти представителя множества (с path compression)
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    // Объединить два множества (union by rank)
    bool unite(int x, int y) {
        int px = find(x);
        int py = find(y);
        
        if (px == py) return false; // уже в одном множестве
        
        if (rank[px] < rank[py]) {
            parent[px] = py;
        } else if (rank[px] > rank[py]) {
            parent[py] = px;
        } else {
            parent[py] = px;
            rank[px]++;
        }
        return true;
    }
    
    // Проверить, принадлежат ли два элемента одному множеству
    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};

// Алгоритм Крускала для MST (минимальное остовное дерево)
ll kruskal(int n, vector<edge>& edges) {
    sort(edges.begin(), edges.end());
    
    DSU dsu(n);
    ll mstWeight = 0;
    int edgesAdded = 0;
    
    for (auto [w, u, v] : edges) {
        if (dsu.unite(u, v)) {
            mstWeight += w;
            edgesAdded++;
            if (edgesAdded == n - 1) break;
        }
    }
    
    return edgesAdded == n - 1 ? mstWeight : -1; // -1 если граф несвязный
}

// Крускал с возвратом рёбер MST
pair<ll, vector<pair<int, int>>> kruskalWithEdges(int n, vector<edge>& edges) {
    sort(edges.begin(), edges.end());
    
    DSU dsu(n);
    ll mstWeight = 0;
    vector<pair<int, int>> mstEdges;
    
    for (auto [w, u, v] : edges) {
        if (dsu.unite(u, v)) {
            mstWeight += w;
            mstEdges.push_back({u, v});
            if (mstEdges.size() == n - 1) break;
        }
    }
    
    return {mstWeight, mstEdges};
}

// Поиск всех компонент связности
vector<vector<int>> findComponents(int n, vector<pair<int, int>>& edges) {
    DSU dsu(n);
    
    for (auto [u, v] : edges) {
        dsu.unite(u, v);
    }
    
    map<int, vector<int>> components;
    for (int i = 0; i < n; i++) {
        components[dsu.find(i)].push_back(i);
    }
    
    vector<vector<int>> result;
    for (auto& [_, comp] : components) {
        result.push_back(comp);
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // Пример: 5 вершин, 7 рёбер
    int n = 5;
    vector<edge> edges = {
        {2, 0, 1},
        {3, 0, 3},
        {6, 0, 4},
        {7, 1, 2},
        {8, 1, 4},
        {4, 2, 3},
        {5, 3, 4}
    };
    
    // Крускал
    auto [mstWeight, mstEdges] = kruskalWithEdges(n, edges);
    
    cout << "MST weight: " << mstWeight << "\n";
    cout << "MST edges:\n";
    for (auto [u, v] : mstEdges) {
        cout << u << " - " << v << "\n";
    }
    
    // DSU пример
    DSU dsu(5);
    dsu.unite(0, 1);
    dsu.unite(1, 2);
    dsu.unite(3, 4);
    
    cout << "Connected (0, 2): " << (dsu.connected(0, 2) ? "yes" : "no") << "\n";
    cout << "Connected (0, 3): " << (dsu.connected(0, 3) ? "yes" : "no") << "\n";
    
    return 0;
}

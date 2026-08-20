#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// ДП на деревьях: максимальный путь от вершины
vector<ll> dfsMax(int u, int parent, vector<vector<int>>& graph, vector<ll>& dp) {
    dp[u] = 0;
    
    for (int v : graph[u]) {
        if (v == parent) continue;
        dfsMax(v, u, graph, dp);
        dp[u] = max(dp[u], dp[v] + 1);
    }
    
    return dp;
}

// ДП на деревьях: количество способов
void dfsCount(int u, int parent, vector<vector<int>>& graph, vector<ll>& dp) {
    dp[u] = 1;
    
    for (int v : graph[u]) {
        if (v == parent) continue;
        dfsCount(v, u, graph, dp);
        dp[u] *= (dp[v] + 1); // +1 для выбора не идти в это поддерево
    }
}

// ДП на деревьях: максимальная сумма независимого множества
void dfsIndependent(int u, int parent, vector<vector<int>>& graph, 
                    vector<ll>& include, vector<ll>& exclude, vector<int>& weight) {
    include[u] = weight[u];
    exclude[u] = 0;
    
    for (int v : graph[u]) {
        if (v == parent) continue;
        dfsIndependent(v, u, graph, include, exclude, weight);
        
        include[u] += exclude[v]; // если включим u, исключим всех детей
        exclude[u] += max(include[v], exclude[v]); // если исключим u, можем выбрать макс
    }
}

// ДП на деревьях: диаметр дерева
pair<ll, ll> dfsDiameter(int u, int parent, vector<vector<int>>& graph) {
    ll maxDepth = 0;
    ll result = 0;
    
    for (int v : graph[u]) {
        if (v == parent) continue;
        auto [childDiameter, childDepth] = dfsDiameter(v, u, graph);
        
        result = max(result, childDiameter);
        result = max(result, maxDepth + childDepth + 1);
        maxDepth = max(maxDepth, childDepth + 1);
    }
    
    return {result, maxDepth};
}

// ДП на деревьях: размер поддерева
void dfsSize(int u, int parent, vector<vector<int>>& graph, vector<int>& size) {
    size[u] = 1;
    
    for (int v : graph[u]) {
        if (v == parent) continue;
        dfsSize(v, u, graph, size);
        size[u] += size[v];
    }
}

// ДП на деревьях: высота поддерева
void dfsHeight(int u, int parent, vector<vector<int>>& graph, vector<ll>& height) {
    height[u] = 0;
    
    for (int v : graph[u]) {
        if (v == parent) continue;
        dfsHeight(v, u, graph, height);
        height[u] = max(height[u], height[v] + 1);
    }
}

// ДП на деревьях: центроид (вершина с минимальным максимальным поддеревом)
int dfsCentroid(int u, int parent, vector<vector<int>>& graph, vector<int>& size, int treeSize) {
    for (int v : graph[u]) {
        if (v == parent) continue;
        if (size[v] > treeSize / 2) {
            return dfsCentroid(v, u, graph, size, treeSize);
        }
    }
    return u;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // Пример: дерево с 6 вершинами
    int n = 6;
    vector<vector<int>> graph(n);
    vector<int> weight = {5, 3, 8, 2, 7, 1};
    
    // Добавляем рёбра (ненаправленные)
    graph[0].push_back(1);
    graph[1].push_back(0);
    graph[0].push_back(2);
    graph[2].push_back(0);
    graph[1].push_back(3);
    graph[3].push_back(1);
    graph[1].push_back(4);
    graph[4].push_back(1);
    graph[2].push_back(5);
    graph[5].push_back(2);
    
    // ДП: максимальный путь
    vector<ll> dpMax(n);
    dfsMax(0, -1, graph, dpMax);
    cout << "Max depth from root: " << dpMax[0] << "\n";
    
    // ДП: размер поддерева
    vector<int> size(n);
    dfsSize(0, -1, graph, size);
    cout << "Subtree sizes: ";
    for (int s : size) cout << s << " ";
    cout << "\n";
    
    // ДП: высота
    vector<ll> height(n);
    dfsHeight(0, -1, graph, height);
    cout << "Heights: ";
    for (ll h : height) cout << h << " ";
    cout << "\n";
    
    // ДП: максимальное независимое множество
    vector<ll> include(n), exclude(n);
    dfsIndependent(0, -1, graph, include, exclude, weight);
    cout << "Max independent set weight: " << max(include[0], exclude[0]) << "\n";
    
    // ДП: диаметр дерева
    auto [diameter, _] = dfsDiameter(0, -1, graph);
    cout << "Tree diameter: " << diameter << "\n";
    
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll INF = 1e18;

// Floyd-Warshall: все пары кратчайших путей
vector<vector<ll>> floydWarshall(int n, vector<vector<ll>>& dist) {
    // dist[i][j] - расстояние от i до j (INF если нет ребра)
    
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
    
    return dist;
}

// Floyd-Warshall с восстановлением пути
pair<vector<vector<ll>>, vector<vector<int>>> floydWarshallWithPath(int n, vector<vector<ll>>& dist) {
    vector<vector<int>> next(n, vector<int>(n, -1));
    
    // Инициализация матрицы next
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && dist[i][j] != INF) {
                next[i][j] = j;
            }
        }
    }
    
    // Floyd-Warshall
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        next[i][j] = next[i][k];
                    }
                }
            }
        }
    }
    
    return {dist, next};
}

// Восстановление пути
vector<int> reconstructPath(int u, int v, vector<vector<int>>& next) {
    if (next[u][v] == -1) return {};
    
    vector<int> path = {u};
    while (u != v) {
        u = next[u][v];
        path.push_back(u);
    }
    return path;
}

// Проверка на отрицательный цикл
bool hasNegativeCycle(vector<vector<ll>>& dist) {
    int n = dist.size();
    for (int i = 0; i < n; i++) {
        if (dist[i][i] < 0) {
            return true;
        }
    }
    return false;
}

// Транзитивное замыкание (есть ли путь между вершинами)
vector<vector<bool>> transitiveClosure(int n, vector<vector<bool>>& adj) {
    vector<vector<bool>> reach = adj;
    
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                reach[i][j] = reach[i][j] || (reach[i][k] && reach[k][j]);
            }
        }
    }
    
    return reach;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n = 4;
    vector<vector<ll>> dist(n, vector<ll>(n, INF));
    
    // Инициализация матрицы расстояний
    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
    }
    
    // Добавляем рёбра
    dist[0][1] = 3;
    dist[0][3] = 7;
    dist[1][2] = 1;
    dist[1][3] = 2;
    dist[2][0] = 2;
    dist[3][2] = 1;
    
    // Floyd-Warshall
    vector<vector<ll>> result = floydWarshall(n, dist);
    
    cout << "Shortest distances (Floyd-Warshall):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (result[i][j] == INF) cout << "INF ";
            else cout << result[i][j] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
